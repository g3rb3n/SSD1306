#ifndef _Graphics2D_H_
#define _Graphics2D_H_

#define BLACK 0
#define WHITE 1

#define SWAP(a, b) { uint8_t t = a; a = b; b = t; }

#include "../screenbuffer/ScreenBuffer.h"

#include "../util/types.h"

namespace g3rb3n
{

  class Graphics2D
  {
    protected:
      ScreenBuffer* buffer;
      uint8_t foregroundColor;

    protected:
      Graphics2D();

    public:
      Graphics2D(ScreenBuffer* buffer);
      ~Graphics2D();

      void begin(void);

      uint8_t width();
      uint8_t height();

      void setColor(uint8_t color);

      void clear();
      void clear(uint8_t c);
      
      void pixel(uint8_t x, uint8_t y);
      
      void drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
      void drawVerticalLine(uint8_t x, uint8_t y, uint8_t len);
      void drawHorizontalLine(uint8_t x, uint8_t y, uint8_t len);

      void drawRectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height);
      void fillRectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height);

      void drawCircle(uint8_t x, uint8_t y, uint8_t radius);
      void fillCircle(uint8_t x0, uint8_t y0, uint8_t radius);

      void setBitmap(uint8_t* pixels, uint8_t page, uint8_t col, uint8_t pages, uint8_t cols);
      void drawBitmap(uint8_t * bitArray);
      void drawBitmap(uint8_t* bitArray, uint8_t x, uint8_t y, uint8_t width, uint8_t height);
      void clearBitmap(uint8_t* bitArray, uint8_t x, uint8_t y, uint8_t width, uint8_t height);

    };

}
#endif
