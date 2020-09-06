#ifndef TOGGLE_BUTTON_HPP
#define TOGGLE_BUTTON_HPP

#include <Arduino.h>

class ToggleButton {
    public:
        ToggleButton(int pin, bool& boolToToggle);

        void updateState();

    private:
        bool& boolToToggle;
        const int pin;
        int state{LOW};
        unsigned long timeWhenPressedInMilliseconds{0};
};

#endif