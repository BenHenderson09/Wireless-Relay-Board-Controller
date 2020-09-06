#ifndef SOLID_LED_HPP
#define SOLID_LED_HPP

class SolidLED {
    public:
        SolidLED(int pin);

        void turnOn();
        void turnOff();

    private:
        const int pin;
};

#endif