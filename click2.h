#pragma once

enum class click_state {pulled, grace_period, pressed, pressed_after_push_event};

class Guzik {
public:
	Guzik(int pin,
			void(*event_click)(void*),  void * event_click_arg=0,
			void(*event_hold)(void *)=0, void * event_hold_arg=0,
			bool analog_pin=false);
	void update(bool debug=false);

private:
	void change_state(click_state new_state, bool debug);
	bool was_button_pressed_before_grace_period();

	int m_pin;
	bool m_analog_pin=false;

	void (* m_event_click)(void*)=0;
	void * m_click_event_arg;
	void (* m_event_hold)(void*)=0;
	void * m_hold_event_arg;
//	void (* m_event_doubleclick)(void)=0;

	unsigned long m_czas_n; //timer for push_event
	unsigned long m_fast_t; //timer_for_grace_period

	click_state m_state = click_state::pulled; // pulled - nic nie naciśnięte. pressed_in_grace_period - naciśnięty klawisz, ale w grace period, który blokuje zdarzenie puszczenia klawisza
	click_state m_state_before_grace_period = click_state::pulled;
};

