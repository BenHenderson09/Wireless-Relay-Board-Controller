#include <Arduino.h>
#include "../../constants/BlinkableLEDConstants.hpp"
#include "BlinkableLED.hpp"

BlinkableLED::BlinkableLED(int pin) : pin{pin}{
  pinMode(pin, OUTPUT);
}

void BlinkableLED::blink(){
  // When the state is updated, the time at which the blink was started will
  // be used to decide when to turn off the LED.
  timeWhenBlinkStartedInMilliseconds = millis();
  turnOn();
}

void BlinkableLED::updateState(){
  // Don't do any unnecessary writes to the pin when it's already turned off.
  if (hasBlinkFinished() && state != LOW){
    turnOff();
  }
}

bool BlinkableLED::hasBlinkFinished(){
  unsigned long millisecondsElapsedSinceBlinkStarted {
    millis() - timeWhenBlinkStartedInMilliseconds
  };

  return millisecondsElapsedSinceBlinkStarted >=
    BlinkableLEDConstants::lengthOfBlinkInMilliseconds;
}

void BlinkableLED::turnOn(){
  digitalWrite(pin, HIGH);
  state = HIGH;
}

void BlinkableLED::turnOff(){
  digitalWrite(pin, LOW);
  state = LOW;
}