#include "I2CIO.h"
#include "ScreenBuffer.h"
#include "SSD1306.h"
#include "Graphics2D.h"

#include <Wire.h>

using namespace g3rb3n;

I2CIO io(0x3C);
ScreenBuffer screen(128, 64, 1);
SSD1306 ssd(&io);
Graphics2D gfx(&screen);

void setup()
{
  setupSerial();
  setupSSD();
  squareCross();
  //squareCross2();
}

void setupSSD()
{
  screen.begin();
  ssd.begin();
  gfx.begin();
  
  gfx.clear();
  ssd.display(screen);
}

void setupSerial()
{
  Serial.begin(230400);
  Serial.println();
}

void loop()
{
}


void lineH(uint8_t x, uint8_t y, uint8_t w)
{
  for (uint8_t i = 0; i < w ; ++i)
  {
    ESP.wdtFeed();
    gfx.pixel(x + i, y, 1);
    if (i % 12 == 0)
      ssd.display(screen);
  }
}

void lineV(uint8_t x, uint8_t y, uint8_t w)
{
  for (uint8_t i = 0; i < w ; ++i)
  {
    ESP.wdtFeed();
    gfx.pixel(x, y + i, 1);
    if (i % 12 == 0)
      ssd.display(screen);
  }
}

void lineD(uint8_t x, uint8_t y, uint8_t w)
{
  for (uint8_t i = 0; i < w ; ++i)
  {
    ESP.wdtFeed();
    gfx.pixel(x + i, y + i, 1);
    if (i % 12 == 0)
      ssd.display(screen);
  }
}

void squareCross2()
{
  lineH(  0,  0, 128);
  lineH(  0, 63, 128);
  lineV(127,  0,  64);
  lineV(  0,  0,  64);
  lineD(0,0,64);
}

void squareCross()
{
  gfx.line(0, 0, 127, 0);
  ssd.display(screen);

  gfx.line(127, 0, 127, 63);
  ssd.display(screen);

  gfx.line(127, 63, 0, 63);
  ssd.display(screen);

  gfx.line(0, 63, 0, 0);
  ssd.display(screen);

  gfx.line(0,0,63,63);
  ssd.display(screen);
  
  gfx.line(63,0,0,63);
  ssd.display(screen);
  
  gfx.line(64,0,127,63);
  ssd.display(screen);
  
  gfx.line(127,0,64,63);
  ssd.display(screen);
  
  delay(500);
}
