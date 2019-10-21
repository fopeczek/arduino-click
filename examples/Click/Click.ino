#include <Arduino.h>
#include <click.h>

Guzik g;
int pin = 2;

void Click(){
    Serial.print("Click!\n");
}

void HoldClick() {
    Serial.print("Hold click!\n");
}

void setup() { 
    g.setupClickHandler(Click);
    g.setupHoldHandler(HoldClick);
    g.setupUsingDigitalPin(pin);
    Serial.begin(9600);
    Serial.print("Setup complete!!\n");
}

void loop() {
    g.update(false);
} 
