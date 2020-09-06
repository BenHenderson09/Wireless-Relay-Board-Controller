#include <Arduino.h>
#include "SolidLED.hpp"

SolidLED::SolidLED(int pin): pin{pin}{
    pinMode(pin, OUTPUT);
};

void SolidLED::turnOn(){
    digitalWrite(pin, HIGH);
}

void SolidLED::turnOff(){
    digitalWrite(pin, LOW);
}