#include <Arduino.h>
#include "ToggleButton.hpp"

ToggleButton::ToggleButton(int pin, bool& boolToToggle)
        : pin{pin}, boolToToggle{boolToToggle}{
    pinMode(pin, INPUT);
};

void ToggleButton::updateState(){
    int previousState = state;
    state = digitalRead(pin);

    if (state == HIGH && previousState == LOW && millis() - timeWhenPressedInMilliseconds >= 500){
        timeWhenPressedInMilliseconds = millis();
        boolToToggle = !boolToToggle;
    }
}