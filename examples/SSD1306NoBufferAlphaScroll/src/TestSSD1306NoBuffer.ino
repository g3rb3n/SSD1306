#include "devices/SSD1306I2CNoBuffer.h"

using namespace g3rb3n;

#define DELAY 0

uint8_t cols = 5;
uint8_t rows = 8;
uint8_t bitmap[] = {
  0x60, 0x1C, 0x13, 0x1C, 0x60,
  0x7F, 0x49, 0x49, 0x49, 0x36,
  0x3E, 0x22, 0x41, 0x41, 0x22,
  0x7F, 0x41, 0x41, 0x22, 0x3E,
  0x7F, 0x49, 0x49, 0x49, 0x49,
  0x7F, 0x09, 0x09, 0x09, 0x09,
  0x3E, 0x41, 0x49, 0x49, 0x3A,
  0x7F, 0x08, 0x08, 0x08, 0x7F
};
uint8_t empty[] = {
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00
};

SSD1306I2CNoBuffer oled(0x3C);

uint32_t count = 0;
uint8_t pos = 0;
bool forward = true;

void setup()
{
  setupSerial();
  setupOled();
}

void setupSerial()
{
  Serial.begin(230400);
  Serial.println();
}

void setupOled()
{
  oled.begin();
  oled.flipVertical(true);
  oled.flipHorizontal(true);
}

bool horizontal = true;
bool vertical = true;
uint8_t divider = oled.width() - cols - 2;

void loop()
{
  long start = micros();
  oled.setBitMap(0, pos, empty, 8, 1);
  oled.setBitMap(0, pos+1, bitmap, rows, cols);
  oled.setBitMap(0, pos+cols+1, empty, 8, 1);
  delay(DELAY);
  
  
  if(count % (divider * 2) == 0)
  {
    horizontal = !horizontal;
    oled.flipHorizontal(horizontal);
  }
  if(count % (divider * 4) == 0)
  {
    vertical = !vertical;
    oled.flipVertical(vertical);
  }
  //Serial.println(micros() - start);
  if(pos == divider)
    forward = false;
  if(pos == 0)
    forward = true;

  if(forward)
    ++pos;
  else
    --pos;

  ++count;
}
