#include "click.h"
#include "Arduino.h"

guzikContext gc;

void onClick() {
	Serial.print ("Click!\n");
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
	set_guzik(&gc, 2, onClick, onDoubleClick, onHold);
}

void loop()
{
	update_guzik(&gc);
}
