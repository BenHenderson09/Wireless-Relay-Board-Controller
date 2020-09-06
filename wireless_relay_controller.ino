#include "LoRa_STM32.hpp"

const int packetReceivedIndicatorPin{PB0};
int packetReceivedIndicatorState{LOW};
const int lengthOfIndicatorBlinkInMilliseconds{100};
const long frequency{433E6};
long int timeWhenPacketReceivedInMilliseconds{0};

const int packetSentIndicatorPin{PC15};
int packetSentIndicatorState{LOW};
const int intervalBetweenPacketSendsInMilliseconds{1000};
unsigned long timeWhenPacketSentInMilliseconds{0};
int packetsSentCounter{0};

void setup() {
  setupPacketIndicators();
  setupLoRa();

  pinMode(PB10, OUTPUT);
  pinMode(PB11, OUTPUT);
}

void loop() {
  if (isAPacketDueToBeSent()) {
    sendPacket();
  }
  
  if (LoRa.parsePacket()) {
    int packet{LoRa.read()};
    bool isFirstRelayTurnedOn{packet & (1 << 1)};
    bool isSecondRelayTurnedOn{packet & 1};
    
    if (isFirstRelayTurnedOn){digitalWrite(PB10, HIGH);}else{digitalWrite(PB10, LOW);}
    if (isSecondRelayTurnedOn){digitalWrite(PB11, HIGH);}else{digitalWrite(PB11, LOW);}
    timeWhenPacketReceivedInMilliseconds = millis();
  }

  handlePacketIndicators();
}

void setupPacketIndicators(){
  pinMode(packetSentIndicatorPin, OUTPUT);
  pinMode(packetReceivedIndicatorPin, OUTPUT);
}

void setupLoRa() {
  if (!LoRa.begin(frequency)) {
    while (1);
  }
  
  //LoRa.onTxDone(onTxDone);
}

void onTxDone() {
  digitalWrite(packetSentIndicatorPin, LOW);
}

bool isAPacketDueToBeSent(){
  return millis() - timeWhenPacketSentInMilliseconds >= intervalBetweenPacketSendsInMilliseconds;
}

void handlePacketIndicators(){
  handlePacketReceivedIndicator();
  handlePacketSentIndicator();  
}

void handlePacketReceivedIndicator() {
  int newPacketReceivedIndicatorState{calculatePacketReceivedIndicatorState()};

  if (newPacketReceivedIndicatorState != packetReceivedIndicatorState){
    packetReceivedIndicatorState = newPacketReceivedIndicatorState;
    digitalWrite(packetReceivedIndicatorPin, packetReceivedIndicatorState);
  }
}

void handlePacketSentIndicator() {
  int newPacketSentIndicatorState{calculatePacketSentIndicatorState()};

  if (newPacketSentIndicatorState != packetSentIndicatorState){
    packetSentIndicatorState = newPacketSentIndicatorState;
    digitalWrite(packetSentIndicatorPin, packetSentIndicatorState);
  }
}

int calculatePacketReceivedIndicatorState(){
  bool hasBlinkFinished {
    millis() - timeWhenPacketReceivedInMilliseconds >= lengthOfIndicatorBlinkInMilliseconds
  };

  int newPacketReceivedIndicatorState;

  if (hasBlinkFinished) {
    return LOW;
  }
  else {
    return HIGH;
  }
}

int calculatePacketSentIndicatorState(){
  bool hasBlinkFinished {
    millis() - timeWhenPacketSentInMilliseconds >= lengthOfIndicatorBlinkInMilliseconds
  };

  int newPacketSentIndicatorState;

  if (hasBlinkFinished) {
    return LOW;
  }
  else {
    return HIGH;
  }
}

void sendPacket(){
  digitalWrite(packetSentIndicatorPin, HIGH);
  timeWhenPacketSentInMilliseconds = millis();
  
  LoRa.beginPacket();
  LoRa.print("Counter from Arduino: ");
  LoRa.print(packetsSentCounter);
  LoRa.endPacket(true);

  digitalWrite(packetSentIndicatorPin, LOW);

  packetsSentCounter++;
}
