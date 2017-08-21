#include "../../src/I2CIO.h"
#include "../../src/Screen.h"
#include "../../src/SSD1306.h"
#include "../../src/Graphics2D.h"

using namespace g3rb3n;

I2CIO io(0x3C);
Screen screen(128, 64, 1);
SSD1306 ssd(&io);
Graphics2D gfx(&screen, &io, &ssd);

void setup()
{
  setupSerial();
  setupSSD();
  alphabet();
}

void alphabet()
{
  String value = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  Serial.println(value);
  gfx.clear(PAGE);
  gfx.setCursor(0,0);
  gfx.print(value);
  gfx.display();
  delay(1000);
}

void setupSSD()
{
  screen.begin();
  ssd.begin();
  gfx.begin();
  
  ssd.invert(false);
  gfx.clear(ALL);
  gfx.display();
}

void setupSerial()
{
  Serial.begin(230400);
  Serial.println();
}

void loop()
{
}
