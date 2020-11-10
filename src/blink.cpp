// Do not remove the include below
#include "blink.h"

Blinker::Blinker(int pin, int time_on, int time_off) {
	m_pin=pin;
	m_time_on=time_on;
	m_blink_times = 0;
	if (time_off <= 0){
		m_time_off=m_time_on;
	}else{
		m_time_off=time_off;
	}
}
void Blinker::blink(int ile){
	m_blink_times=ile;
	catode_on();
}


void Blinker::catode_on(){
	digitalWrite(m_pin, HIGH);
	m_blink_times --;
	m_catode.set_timer(m_time_on, [this](){this->catode_off();});
}

void Blinker::catode_off(){
	digitalWrite(m_pin, LOW);
	if (m_blink_times != 0){
		m_catode.set_timer(m_time_off, [this](){this->catode_on();});
	}
}

void Blinker::update(){
	m_catode.update();
}
