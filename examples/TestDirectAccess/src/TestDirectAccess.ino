#define _DEBUG_DMA_


#include "SSD1306.h"
#include "SSD1306Control.h"
#include "DirectScreenMemory.h"
#include "PageUpdateScreenBuffer.h"
#include "PartialUpdateScreenBuffer.h"
#include "I2CIO.h"
#include <Wire.h>

#include "util/font5x7.h"
#include "logos/SparkFunLogo.h"

using namespace g3rb3n;

ScreenBuffer buffer(128, 64, 1);
//PageUpdateScreenBuffer buffer(128, 64, 1);
//PartialUpdateScreenBuffer buffer(128, 64, 1);
I2CIO io(0x3C);
SSD1306 oled(&buffer, &io);
DirectScreenMemory da(&io);
//SSD1306Control ctrl(&io);
//DirectScreenMemory da(&ctrl);

uint8_t bitmap[384];
uint8_t bm_cols = 64;
uint8_t bm_rows = 6;
void setup()
{
  setupSerial();
  setupOled();
}

void getChar(uint8_t* data, uint8_t* font, uint8_t off, uint8_t width, uint8_t c)
{
  for (uint8_t i = 0 ; i < width ; ++i)
  {
    data[i] = pgm_read_byte(font + off + c * width + i);
  }
}

void printBytes(uint8_t* bytes, uint8_t len)
{
  for (uint8_t i = 0 ; i < len ; ++i)
  {
    uint8_t b = *(bytes + i);
    Serial.print(b, 16);
    Serial.print(' ');
  }
  Serial.println();
}

void placeCharBitmap(uint8_t r, uint8_t c, uint8_t ch)
{
  uint8_t pos = r * 128 + c;
  for (uint8_t i = 0 ; i < 5 ; ++i)
    da.set(pgm_read_byte(font5x7 + 6 + ch * 5 + i), pos + i);
}

void placeCharBitmap2(uint8_t r, uint8_t c, uint8_t ch)
{
  uint16_t pos = r * 128 + c;
  uint8_t bytes[5];
  getChar(bytes, font5x7, 6, 5, ch);
  da.setBytemap(bytes, pos, 5, 5);
}

void getLogoBytes(uint8_t* data, uint16_t len, uint8_t* logo, uint8_t off)
{
  Serial.println("getLogoBytes");
  for (uint16_t i = 0 ; i < len ; ++i)
  {
    data[i] = pgm_read_byte(logo + off + i);
  }
}

void placeLogo(uint8_t row, uint8_t col, uint8_t* logo, uint8_t rows, uint8_t cols)
{
  Serial.println("placeBitmap");
  uint16_t pos = row * 128 + col;
  uint16_t size = rows * cols;
  uint8_t bytes[size];
  getLogoBytes(bytes, size, logo, 0);
  da.setBytemap(bytes, pos, size, cols);
}

void placeBitmap(uint8_t row, uint8_t col, uint8_t* bitmap, uint8_t rows, uint8_t cols)
{
  Serial.println("placeBitmap");
  uint16_t pos = row * 128 + col;
  uint16_t size = rows * cols;
  da.setBytemap(bitmap, pos, size, cols);
}

void setupOled()
{
  oled.begin();
  oled.flipVertical(false);
  oled.flipHorizontal(false);
  oled.setFontType(0);
  oled.clear();
  oled.display();
  /*
  Serial.println(font5x7[0]);
  Serial.println(font5x7[1]);
  Serial.println(font5x7[2]);
  Serial.println(font5x7[3]);
  Serial.println(font5x7[4]);
  Serial.println(font5x7[5]);
  Serial.println(font5x7[6]);
  uint8_t bytes[5];
  getChar(bytes, font5x7, 6, 5, 'A');
  printBytes(bytes, 5);
  da.setBytemap(bytes, 4*128 + 64, 5, 5);
  getChar(bytes, font5x7, 6, 5, 'A'+1);
  printBytes(bytes, 5);
  da.setBytemap(bytes, 4*128 + 70, 5, 5);
  placeCharBitmap2(4, 76, 'C');
  delay(1000);
  Serial.println("Alphabet");
  for (uint8_t r = 0 ; r < 8 ; ++r)
    for (uint8_t c = 0 ; c < 52 ; ++c)
      placeCharBitmap2(r, c * 5, 'A' + c);
  delay(1000);
  //oled.clear();
  //oled.display();
*/
  Serial.println("Logo");
  placeLogo(0, 64, SPARK_FUN_LOGO, 6, 64);
  delay(1000);
  getLogoBytes(bitmap, bm_cols * bm_rows, SPARK_FUN_LOGO, 0);
  delay(500);
  da.setBytemap(1,4, bitmap, 384, 64);

}


void setupSerial()
{
  Serial.begin(230400);
  Serial.println();
}

uint8_t chars[] = {
  0x60, 0x1C, 0x03, 0x1C, 0x60,
  0x7F, 0x49, 0x49, 0x49, 0x36,
  0x1C, 0x22, 0x41, 0x41, 0x22
};

uint8_t col = 0;
bool forward = true;
void loop()
{

  long start = micros();
  da.setBytemap(col, col / 4, bitmap, 384, 64);
  Serial.println(micros() - start);
  if(forward)
    ++col;
  else
    --col;
  if(col == 64)
    forward = false;
  if(col == 0)
    forward = true;

/*
  Serial.println("Alphabet");
  for (uint8_t r = 0 ; r < 8 ; ++r)
    for (uint8_t c = 0 ; c < 52 ; ++c)
      placeCharBitmap2(r, c * 5, 'A' + c);
*/
  //da.setBytemap(chars, 65, 15, 5);
//  Serial.println("ABC");
//  da.setBytemap(chars, 3*128+ 65, 15, 5);
}
