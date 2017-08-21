#include "SSD1306.h"
#include "PageUpdateScreenBuffer.h"
#include "PartialUpdateScreenBuffer.h"
#include "I2CIO.h"

#include <Wire.h>

using namespace g3rb3n;

//ScreenBuffer buffer(128, 64, 1);
//PageUpdateScreenBuffer buffer(128, 64, 1);
PartialUpdateScreenBuffer buffer(128, 64, 1);
I2CIO io(0x3C);
SSD1306 oled(&buffer, &io);

void setup()
{
  setupSerial();
  setupOled();
  oled.setCursor(1,0);
  oled.print("12345678901234567890");
  oled.display();

  Serial.println("Setup");
  for (int i = 0 ; i < 128 ; ++i)
  {
    oled.drawChar(i, 0, '0');
    oled.display();
    delay(25);
  }
}

void setupOled()
{
  oled.begin();
  oled.clear();
  oled.display();
}

void setupSerial()
{
  Serial.begin(230400);
  Serial.println();
}

void loop()
{
}
