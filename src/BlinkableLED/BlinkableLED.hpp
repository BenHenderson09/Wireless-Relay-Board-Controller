#ifndef BLINKABLE_LED_HPP
#define BLINKABLE_LED_HPP

class BlinkableLED {
  public:
    BlinkableLED(int pin);
  
    void blink();
    void updateState();

  private:
    const int lengthOfBlinkInMilliseconds{100};
    const int pin;
    bool state{LOW};
    unsigned long timeWhenBlinkStartedInMilliseconds;

    bool hasBlinkFinished();
    void turnOn();
    void turnOff();
};

#endif
