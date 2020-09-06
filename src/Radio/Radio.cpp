#include "../LoRa_STM32/LoRa_STM32.hpp"
#include "Radio.hpp"

void Radio::init(){
    if (!LoRa.begin(radioFrequency)) {
        while (1);
    }

    LoRa.setTxPower(15);
}

void Radio::sendByte(uint8_t byte){
    LoRa.beginPacket();
    LoRa.write(byte);
    LoRa.endPacket(true);
}

void Radio::receiveByte(void(*receiveByteCallback)(uint8_t)){
    if (LoRa.parsePacket()){
        (*receiveByteCallback)(LoRa.read());
    }
}