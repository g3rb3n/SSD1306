#include "I2CIO.h"
#include "SSD1306.h"

using namespace g3rb3n;

I2CIO io(0x3C);
SSD1306 oled(&io);

void setup()
{
  setupSerial();
  Serial.println("Serial setup");
  
  setupSSD();
  Serial.println("OLED setup");
}

void setupSSD()
{
  oled.begin();
  oled.clear(ALL);
  oled.display();
}

void setupSerial()
{
  Serial.begin(230400);
  Serial.println();
}

int value = 0;
void loop()
{
  ++value;
  Serial.println(value);
  oled.clear(PAGE);
  oled.setCursor(0,0);
  oled.print(value);
  oled.display(); 
}
