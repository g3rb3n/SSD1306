#include "devices/SSD1306I2C.h"

using namespace g3rb3n;

SSD1306I2C oled(0x3C, 128, 48);

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
  setLayout(6, 64, 0, 32);
}

void test()
{
  //oled.flipVertical(true);
  //oled.flipHorizontal(true);
  oled.clear();
  oled.drawCircle(32, 24, 24);
  oled.drawRectangle(0, 0, 64, 48);
  oled.drawLine(0, 0, 63, 47);
  oled.setCursor(5,10);
  Serial.print("Hello world");
  oled.setCursor(0,0);
  oled.print("Hello world");
  oled.display();
}

void loop()
{
}
