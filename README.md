
Main features:
- Multiple communication bus protocols support: I2C and SPI.
- 

This library has mainly two parts. One for drawing graphics and one for communication with the OLED MCU.

IOBusProtocol
I2CBusProtocol
SPIBusProtocol
Basic read write functionality over various buses.
- write(uint8_t byte);
- write(uint8_t* byte, uint8_t len);


SSD1306Control
SSD1306 driver.

ScreenBuffer
