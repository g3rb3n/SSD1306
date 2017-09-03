/**
* Generic C/C++
*/
#include <unity.h>

#include "../src/screenbuffer/ScreenBuffer.h"

using namespace g3rb3n;

#ifndef UNIT_TEST


uint8_t pixel(uint8_t *buffer, uint8_t width, uint8_t height, uint8_t x, uint8_t y)
{
  uint16_t pos = (y / 8) * width + x;
  uint8_t bit = y % 8;
  return (buffer[pos] >> bit) & 0x01;
}

uint16_t colored(uint8_t *buffer, uint8_t width, uint8_t height)
{
  uint16_t sum = 0;
  for (uint8_t x = 0 ; x < width ; ++x)
    for (uint8_t y = 0 ; y < height ; ++y)
      sum += pixel(buffer, width, height, x, y);
  return sum;
}

void drawBitmap(void) {
  uint8_t bitmapWidth = 16;
  uint8_t bitmapHeight = 16;
  uint8_t bitmap[] = {
    0x00, 0xFE, 0xFE, 0xFE, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0xFE, 0xFE, 0xFE, 0x00,
    0x00, 0x7F, 0x7F, 0x7F, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x7F, 0x7F, 0x7F, 0x00
  };
  uint16_t bitmapSum = colored(bitmap, bitmapWidth, bitmapHeight);
  screen.drawBitmap(bm, 0, 0, bitmapWidth, bitmapHeight);
  uint16_t screenSum = colored(screen._buffer(), screen.width(), screen.height());
  
  TEST_ASSERT_EQUAL(bitmapSum, screenSum);
}

int main(int argc, char **argv) 
{
  ScreenBuffer screen(128, 64, 1);

  UNITY_BEGIN();

  RUN_TEST(drawBitmap);

  UNITY_END();  // setup code...

  return 0
}

#endif
