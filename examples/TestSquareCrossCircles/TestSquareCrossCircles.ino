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

void loop()
{
  squareCross();
}

void squareCross2()
{
  oled.line(0, 0, 127, 0);
  oled.line(127, 0, 127, 63);
  oled.line(127, 63, 0, 63);
  oled.line(0, 63, 0, 0);
  oled.line(0,0,63,63);
  oled.line(63,0,0,63);
  oled.line(64,0,127,63);
  oled.line(127,0,64,63);
  circles2(32, 32);
  circles2(96, 32);
}


void squareCross()
{
  oled.line(0, 0, 127, 0);
  oled.display();
  ESP.wdtFeed();

  oled.line(127, 0, 127, 63);
  oled.display();
  ESP.wdtFeed();

  oled.line(127, 63, 0, 63);
  oled.display();
  ESP.wdtFeed();

  oled.line(0, 63, 0, 0);
  oled.display();
  ESP.wdtFeed();

  oled.line(0,0,63,63);
  oled.display();
  ESP.wdtFeed();
  
  oled.line(63,0,0,63);
  oled.display();
  ESP.wdtFeed();
  
  oled.line(64,0,127,63);
  oled.display();
  ESP.wdtFeed();
  
  oled.line(127,0,64,63);
  oled.display();
  ESP.wdtFeed();

  circles(32, 32);

  circles(95, 32);
  
  delay(500);
}

void circles(uint8_t x, uint8_t y)
{
  for (uint i = 0 ; i < 10 ; ++i)
  {
    oled.circle(x, y, 32 - 3*i);
    oled.display();
    ESP.wdtFeed();
  }
}

void circles2(uint8_t x, uint8_t y)
{
  for (uint i = 0 ; i < 10 ; ++i)
  {
    oled.circle(x, y, 32 - 3*i);
  }
}
