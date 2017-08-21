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

long count = 0;
long start;
long now;

void loop()
{
  if (!start)
  {
    start = micros();
    now = start + 100000;
  }

  oled.setCursor(8,0);
  float rate = static_cast<float>(count) / (now - start) * 1000000;
  oled.print(rate, 2);

  uint8_t x = count % 64;
  uint8_t y = count % 64;
  oled.line(x, y, 127-x, 63-y);

  if (x == 0)
    oled.clear();
  oled.display();

  now = micros();
  ++count;
}
