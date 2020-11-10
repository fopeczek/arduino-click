#include "blink.h"
#include "demo.h"

Blinker b(LED_BUILTIN, 1000, 500);

void setup(){
	pinMode(LED_BUILTIN, OUTPUT);
	b.blink(10);
}

void loop(){
	b.update();
}
