# Wireless Relay Board Controller
A portable remote controller which is used to communicate with a
[relay board](https://github.com/BenHenderson09/Wireless-Relay-Board) to turn
on/off mains appliances.

![](https://github.com/BenHenderson09/Wireless-Relay-Board-Controller/blob/master/controller.jpg)

## Details
- Controls the state of a relay board via radio signals.
- A LoRa SX1278 acts as a transceiver for both sending
commands and receiving responses from the board.
- An STM32F103C "Blue Pill" development board works with the LoRa module to manage communications.
- Power is provided at 5V from a rechargeable LiPo battery.