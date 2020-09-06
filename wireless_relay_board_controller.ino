#include "src/Radio/Radio.hpp"
#include "src/BlinkableLED/BlinkableLED.hpp"
#include "src/SolidLED/SolidLED.hpp"
#include "src/ToggleButton/ToggleButton.hpp"

// Radio
Radio radio;

// LEDs
const int txLEDPin{PC15};
const int rxLEDPin{PB0};
const int firstRelayLEDPin{PB10};
const int secondRelayLEDPin{PB11};

BlinkableLED rxLED{rxLEDPin};
BlinkableLED txLED{txLEDPin};
SolidLED firstRelayLED{firstRelayLEDPin};
SolidLED secondRelayLED{secondRelayLEDPin};

// Relays
bool isFirstRelayTurnedOn{false};
bool isSecondRelayTurnedOn{false};

// Buttons
const int firstButtonPin{PA0};
const int secondButtonPin{PA2};

ToggleButton firstButton{firstButtonPin, isFirstRelayTurnedOn};
ToggleButton secondButton{secondButtonPin, isSecondRelayTurnedOn};

void setup() {
  radio.init();
}

void loop() {
  int initialRelayStates{serializeRelayStates()};

  radio.receiveByte(&receiveByteCallback);
  firstButton.updateState();
  secondButton.updateState();
  txLED.updateState();
  rxLED.updateState();

  int updatedRelayStates{serializeRelayStates()};

  if (updatedRelayStates != initialRelayStates){
    radio.sendByte(updatedRelayStates);
    txLED.blink();
  }
}

uint8_t serializeRelayStates(){
  // Bit 0 represents the state of the second relay, bit 1 represents the state of the first relay.
  return (isFirstRelayTurnedOn << 1) | isSecondRelayTurnedOn;
}

void receiveByteCallback(uint8_t byte){
  bool isFirstRelayTurnedOn{byte & (1 << 1)};
  bool isSecondRelayTurnedOn{byte & 1};
  
  isFirstRelayTurnedOn ? firstRelayLED.turnOn() : firstRelayLED.turnOff();
  isSecondRelayTurnedOn ? secondRelayLED.turnOn() : secondRelayLED.turnOff();

  rxLED.blink();
}