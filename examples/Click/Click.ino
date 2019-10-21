#include "click2.h"
#include "Arduino.h"
#include "function.h"

Guzik g;

void onClick(String c) {
	Serial.print (c);
	Serial.print ("\n");
}

void onDoubleClick() {
	//nothing
}

void onHold(){
	Serial.print ("hold\n");
}

void setup()
{
	Serial.begin(9600);
	g.setupUsingDigitalPin(2);
	g.setupClickHandler([](){onClick("Click!");} );
}

void loop()
{
	g.update(1);
}
