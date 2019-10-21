#pragma once
#include "function.h"
enum class click_state {pulled, grace_period, pressed, pressed_after_push_event};

void nofun();

class Guzik {
public:
	Guzik() : m_use_hold(false), m_pin(-1), m_analog_pin(false), m_event_click(nofun), m_event_hold(nofun) {} // @suppress("Class members should be properly initialized")
	void update(bool debug=false);
	void setupUsingDigitalPin(int pin);
	void setupUsingAnalogPin(int pin);
	void setupClickHandler(TransientFunction<void(void)> event_click);
	void setupHoldHandler(TransientFunction<void(void)> event_hold);

private:
	void change_state(click_state new_state, bool debug);
	bool was_button_pressed_before_grace_period();
	bool m_use_hold;

	int m_pin;
	bool m_analog_pin=false;

	TransientFunction<void(void)> m_event_click;
	TransientFunction<void(void)> m_event_hold;
//	void (* m_event_doubleclick)(void)=0;

	unsigned long m_czas_n; //timer for push_event
	unsigned long m_fast_t; //timer_for_grace_period

	click_state m_state = click_state::pulled; // pulled - nic nie naciśnięte. pressed_in_grace_period - naciśnięty klawisz, ale w grace period, który blokuje zdarzenie puszczenia klawisza
	click_state m_state_before_grace_period = click_state::pulled;
};

