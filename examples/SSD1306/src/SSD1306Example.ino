#include "devices/SSD1306I2C.h"

using namespace g3rb3n;

SSD1306I2C oled(0x3C);

void setup()
{
  setupSerial();
  setupOled();
  test();
}

void setupSerial()
{
  Serial.begin(230400);
  Serial.println();
}

void setupOled()
{
  oled.begin();
}

void test()
{
  oled.flipVertical(true);
  oled.flipHorizontal(true);
  oled.clear();
//  oled.drawCircle(63, 31, 31);
//  oled.drawRectangle(0, 0, 127, 63);
//  oled.drawLine(0, 0, 127, 63);
  Serial.print("Hello world");
  oled.setCursor(0,0);
  oled.print("Hello world");
  oled.display();
}

void loop()
{
}
