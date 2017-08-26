# A fast and flexible library for the SSD1306 OLED screens #

## Example ##
```
#include "devices/SSD1306I2C.h"

using namespace g3rb3n;

SSD1306I2C oled(0x3C);

void setup()
{
  Serial.begin(230400);
  Serial.println();
  oled.begin();
}

void loop()
{
  oled.drawCircle(63, 31, 31);
  oled.drawRectangle(0, 0, 127, 63);
  oled.drawLine(0, 0, 127, 63);
  oled.setCursor(0,0);
  oled.print("Hello world");
  oled.display();
}
```
## Main features ##
- Multiple communication bus protocols support: I2C and SPI.
- Multiple buffering options: Direct write, full buffered, page buffered, byte buffered.
- Multiple font support.
- Separation of driver/io and GFX/buffers.
- OOP


This library has mainly two parts. One for drawing graphics and one for communication with the OLED MCU.

## Devices ##
Utility implementations which should make it easy to implement the library. 
- SSD1306
Basic SSD1306 OLED screen graphics and driver in one.
- SSD1306I2C
Basic SSD1306 OLED screen graphics and driver in one for I2C.
- SSD1306I2CNoBuffer
Basic SSD1306 OLED screen driver for low memory requirements for I2C.

## IO ##
- IOBus (Base)
- I2CBus
- SPIBus
Basic read / write functionality over various buses.

- CommandDataIO
For the SSD1306 command / data protocol structure.

## Drivers ##
- SSD1306Driver
A C++ driver for the SSD1306 OLED that exposes all functionality specified in the docs.
 
## ScreenBuffers ##
- ScreenBuffer
Byte buffer which supports full updates.
- PageUpdateScreenBuffer
Byte buffer which supports paged updates.
- ByteUpdateScreenBuffer
Byte buffer which supports updates per changed byte.

## ScreenMap ##
Direct write to SSD1306 RAM support.

## Fonts ##
A C++ fonts library.

## GFX ##
- Graphics2D
Basic 2D graphics for pixel based operations.

- GraphicsPrint
For writing fonts to the screen buffer.

