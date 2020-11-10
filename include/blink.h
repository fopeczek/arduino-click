// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _blink_H_
#define _blink_H_
#include "Arduino.h"
#include "timer.h"
//add your includes for the project blink here


class Blinker{
public:
	Blinker(int pin, int time_on, int time_off = 0);
	void blink(int ile);
	void update();
private:
	void catode_on();
	void catode_off();
	mikTimer m_catode;
	int m_pin;
	int m_blink_times;
	int m_time_on;
	int m_time_off;
};



//Do not add code below this line
#endif /* _blink_H_ */
