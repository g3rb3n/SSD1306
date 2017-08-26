#include "devices/SSD1306I2CNoBuffer.h"

using namespace g3rb3n;

#define DELAY 0

uint8_t cols = 5;
uint8_t rows = 8;
uint8_t bitmap[] = {
  0x60, 0x1C, 0x13, 0x1C, 0x60,
  0x7F, 0x49, 0x49, 0x49, 0x36,
  0x1C, 0x36, 0x41, 0x36, 0x22,
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

void test()
{
  clear();
  oled.flipHorizontal(false);
  oled.flipVertical(false);
  setAlphabet(0);
  setAlphabet(60);
  setAlphabet(120);
  delay(500);
  
  Serial.println("Flip horizontal");
  clear();
  oled.flipHorizontal(true);
  setAlphabet(0);
  setAlphabet(60);
  setAlphabet(120);
  delay(500);

  Serial.println("Flip vertical");
  clear();
  oled.flipVertical(true);
  setAlphabet(0);
  setAlphabet(60);
  setAlphabet(120);
  delay(500);
  
  Serial.println("Set display off");
  oled.setDisplayOn(false);  
  delay(500);

  Serial.println("Set display on");
  oled.setDisplayOn(false);
  delay(500);
  
  Serial.println("Set entire display off");
  oled.setEntireDisplayOn(false);
  delay(500);

  Serial.println("Set entire display on");
  oled.setEntireDisplayOn(true);
  delay(500);
  
}

void clear()
{
  for (uint8_t i = 0 ; i < 127 ; ++i)
    oled.setBitMap(0, pos, empty, 8, 1);
}

void setAlphabet(uint8_t pos)
{
  oled.setBitMap(0, pos, empty, 8, 1);
  oled.setBitMap(0, pos+1, bitmap, rows, cols);
  oled.setBitMap(0, pos+cols+1, empty, 8, 1);  
}

void loop()
{
  ++count;
}
