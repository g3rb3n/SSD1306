#include "devices/SSD1306.h"
#include "screenbuffer/PageUpdateScreenBuffer.h"
#include "screenbuffer/ByteUpdateScreenBuffer.h"
#include "io/I2CBus.h"

#include <Wire.h>

//#define WIRE_SUPPORTS_GET_CLOCK

using namespace g3rb3n;

//ScreenBuffer buffer(128, 64, 1);
//PageUpdateScreenBuffer buffer(128, 64, 1);
ByteUpdateScreenBuffer buffer(128, 64, 1);
I2CBus io(0x3C);
SSD1306 oled(&io, &buffer);

long count = 0;
long last = 0;
long draw = 0;
long display = 0;
long total = 0;
bool whiteMode = false;
bool xMode = false;
uint8_t step = 32;
void (*function)();

uint8_t bitmapWidth = 16;
uint8_t bitmapHeight = 16;
uint8_t bitmap[] = {
  0x00, 0xFE, 0xFE, 0xFE, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0xFE, 0xFE, 0xFE, 0x00,
  0x00, 0x7F, 0x7F, 0x7F, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x7F, 0x7F, 0x7F, 0x00
};

void setup()
{
  setupSerial();
  setupOled();
}

void setupOled()
{
  oled.begin();
  oled.flipVertical(true);
  oled.flipHorizontal(true);
  oled.clear();
  oled.display();
}

void setupSerial()
{
  Serial.begin(230400);
  Serial.println();
}

void reportOLED(String name, long value, String units, uint8_t row)
{
  oled.setCursor(row, 0);
  oled.print(value);
  oled.print(units);
}

void reportSerial(String name, long value, String units)
{
  Serial.print(name);
  Serial.print(':');
  Serial.print(value);
  Serial.print(units);
  Serial.print(' ');
}

void lines()
{
  uint16_t xD =  xMode ? count % step : step - 1;
  uint16_t yD = !xMode ? count % step : 0;
  xD *= 128; 
  xD /= step;
  yD *= 64;
  yD /= step;
  oled.drawLine(xD, yD, 127 - xD, 63 - yD);  
}

void circles()
{
  uint16_t rD = count % step;
  rD *= 32;
  rD /= step;
  oled.drawCircle(63, 31, rD);  
}

void bitmaps()
{
  uint16_t xD =  xMode ? count % step : step - 1;
  uint16_t yD = !xMode ? count % step : 0;
  //uint16_t xD = count % step;
  //uint16_t yD = 0;
  //  xD *= (128 - 16); 
  //  xD /= step;
  //  yD *= (64 - 16);
  //  yD /= step;
  //  if (xMode) oled.drawBitmap(bitmap, xD, yD, bitmapWidth, bitmapHeight);
  //  else oled.clearBitmap(bitmap, xD, yD, bitmapWidth, bitmapHeight);
  oled.drawBitmap(bitmap, 32 + xD, yD, bitmapWidth, bitmapHeight);
}

void loop()
{
  long start = micros();

  if (count % (step * 4) == 0)
  {
    switch((count / (step * 4)) % 3)
    {
      case 0 : function = bitmaps; break;
      case 1 : function = lines; break;
      case 2 : function = circles; break;
      default : function = lines; break;
    }
  }
  if (count % (step * 2) == 0)
  {
    whiteMode = !whiteMode;
    oled.setColor(whiteMode ? 1 : 0);
  }
  if (count % step == 0)
  {
    xMode = !xMode;
  }

  start = micros();
  
  function();
  #ifdef WIRE_SUPPORTS_GET_CLOCK
    reportOLED("I2C", Wire.getClock() / 1000, "kHz", 3);
  #endif
  reportOLED("CPU", F_CPU / 1000000, "MHz", 4);
  reportOLED("draw", draw, "us", 5);
  reportOLED("display", display, "us", 6);
  reportOLED("total", total, "us", 7);

  draw = micros() - start;

  oled.display();

  display = micros() - start;

  reportSerial("draw", draw, "us");
  reportSerial("display", display, "us");
  reportSerial("total", total, "us");
  Serial.println();

  total = micros() - last;
  last = micros();

  ++count;
}
