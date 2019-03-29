#include "Arduino.h"
#include "click2.h"
//#include <Streaming.h>

#define CZAS_TRZYMANIA 1000
#define GRACE_PERIOD 50 //Time after letting the push button go, to prevent re-bounce effects.


static String state_to_string(click_state state) {
	if(state == click_state::grace_period) {
		return "grace_period";
	} else if (state == click_state::pressed) {
		return "pressed";
	} else if (state == click_state::pulled) {
		return "pulled";
	} else if (state == click_state::pressed_after_push_event) {
		return "pressed_after_push_event";
	} else {
		return "Unknown state";
	}
}

void Guzik::change_state(click_state new_state, bool debug) {
	if(debug) {
		Serial.print(millis());
		Serial.print(": ");

	}
	if (new_state == click_state::grace_period) {
		if(m_state==click_state::grace_period) {//We are aborting
			if(debug) {
				Serial.print("Click state revert: ");
				Serial.print(state_to_string(click_state::grace_period));
				Serial.print("->");
				Serial.print(state_to_string(m_state_before_grace_period));
				Serial.print("\n");
			}
			m_state=m_state_before_grace_period;
		} else {
			if(debug) {
				Serial.print("Click state change: ");
				Serial.print(state_to_string(m_state));
				Serial.print(" from (");
				Serial.print(state_to_string(m_state_before_grace_period));
				Serial.print(")->");
				Serial.print(state_to_string(new_state));
				Serial.print("\n");
			}
			m_state_before_grace_period=m_state;
			m_state=click_state::grace_period;
			m_fast_t=millis();
		}
	} else {
		if (debug) {
			Serial.print("Click state change: ");
			Serial.print(state_to_string(m_state));
			Serial.print("->");
			Serial.print(state_to_string(new_state));
			Serial.print("\n");
		}
		m_state=new_state;
	}
}

bool Guzik::was_button_pressed_before_grace_period() {
	if(m_state_before_grace_period == click_state::pressed || m_state_before_grace_period == click_state::pressed_after_push_event) {
		return true;
	} else if(m_state_before_grace_period == click_state::pulled ) {
		return false;
	} else {
		Serial.print("Impossible state in was_button_pressed_before_grace_period\n");
		return false;
	}
}

void Guzik::update(bool debug) {

	bool read;
	if(m_analog_pin) {
		int i_read=analogRead(m_pin);
		read=i_read>511;
	} else {
		read=digitalRead(m_pin);
	}

	if(m_state== click_state::grace_period) {
		if (millis() - GRACE_PERIOD > m_fast_t) {
			if (read != was_button_pressed_before_grace_period()) {
				if(m_state_before_grace_period == click_state::pulled) {
					change_state(click_state::pressed, debug);
					m_czas_n=millis();
				} else if(m_state_before_grace_period == click_state::pressed) {
					change_state(click_state::pulled, debug);
					m_event_click(m_click_event_arg);
				} else if(m_state_before_grace_period == click_state::pressed_after_push_event) {
					change_state(click_state::pulled, debug);
				}
			} else {
				change_state(click_state::grace_period, debug);
			}
		}
	} else if(m_state== click_state::pulled) {
		if(read) {
			change_state(click_state::grace_period, debug);
		}
	} else if(m_state== click_state::pressed) {
		if(read) {
			if(millis() - CZAS_TRZYMANIA > m_czas_n) {
				change_state(click_state::pressed_after_push_event, debug);
				if(m_event_hold) {
					m_event_hold(m_hold_event_arg);
				} else {
					m_event_click(m_click_event_arg);
				}
			}
		} else {
			change_state(click_state::grace_period, debug);
		}
	} else if(m_state==click_state::pressed_after_push_event) {
		if(not read) {
			change_state(click_state::pulled, debug);
		}
	}
}

Guzik::Guzik(int pin,
		void(*event_click)(void*),  void * event_click_arg,
		void(*event_hold)(void *), void * event_hold_arg,
		bool analog_pin):
			m_pin(pin), m_analog_pin(analog_pin),
			m_event_click(event_click), m_click_event_arg(event_click_arg),
			m_event_hold(event_hold), m_hold_event_arg(event_hold_arg),
			m_czas_n(0), m_fast_t(millis()),
			m_state(click_state::grace_period),
			m_state_before_grace_period(click_state::pulled)
{
		pinMode(pin, INPUT);
}
