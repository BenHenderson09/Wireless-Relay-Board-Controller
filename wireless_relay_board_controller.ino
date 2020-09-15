#include "src/Radio/Radio.hpp"
#include "src/BlinkableLED/BlinkableLED.hpp"
#include "src/SolidLED/SolidLED.hpp"
#include "src/ToggleButton/ToggleButton.hpp"
#include "constants/PinConstants.hpp"

// Radio
Radio radio;

// LEDs
BlinkableLED rxLED{PinConstants::rxLEDPin};
BlinkableLED txLED{PinConstants::txLEDPin};
SolidLED firstRelayLED{PinConstants::firstRelayLEDPin};
SolidLED secondRelayLED{PinConstants::secondRelayLEDPin};

// Relays
bool isFirstRelayTurnedOn{false};
bool isSecondRelayTurnedOn{false};

// Buttons
ToggleButton firstButton{PinConstants::firstButtonPin, isFirstRelayTurnedOn};
ToggleButton secondButton{PinConstants::secondButtonPin, isSecondRelayTurnedOn};

void setup() {
  radio.init();
}

void loop() {
  uint8_t initialRelayStates{serializeRelayStates()};

  radio.receiveByte(&receiveByteCallback);
  updateComponentStates();
  sendRelayStatesIfChanged(initialRelayStates);
}

uint8_t serializeRelayStates(){
  // Bit 0 represents the state of the second relay, bit 1 represents the state of the first relay.
  return (isFirstRelayTurnedOn << 1) | isSecondRelayTurnedOn;
}

void updateComponentStates(){
  firstButton.updateState();
  secondButton.updateState();
  txLED.updateState();
  rxLED.updateState();
}

void receiveByteCallback(uint8_t byte){
  bool isFirstRelayTurnedOn{byte & (1 << 1)};
  bool isSecondRelayTurnedOn{byte & 1};
  
  isFirstRelayTurnedOn ? firstRelayLED.turnOn() : firstRelayLED.turnOff();
  isSecondRelayTurnedOn ? secondRelayLED.turnOn() : secondRelayLED.turnOff();

  rxLED.blink();
}

void sendRelayStatesIfChanged(uint8_t initialRelayStates){
  uint8_t updatedRelayStates{serializeRelayStates()};

  if (updatedRelayStates != initialRelayStates){
    radio.sendByte(updatedRelayStates);
    txLED.blink();
  }
}