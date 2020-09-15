#ifndef RADIO_HPP
#define RADIO_HPP

class Radio {
    public:
        void init();
        void sendByte(uint8_t byte);
        void receiveByte(void(*receiveByteCallback)(uint8_t));
};

#endif