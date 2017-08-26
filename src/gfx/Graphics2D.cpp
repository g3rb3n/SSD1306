#include "Graphics2D.h"

#include <Arduino.h>
#define ABS(a) a > 0 ? a : -a
#define swap(a, b) { uint8_t t = a; a = b; b = t; }

namespace g3rb3n
{


  Graphics2D::Graphics2D()
  {
  }

  Graphics2D::Graphics2D(ScreenBuffer* _buffer) :
    buffer(_buffer)
  {
  }

  Graphics2D::~Graphics2D()
  {
  }

  void Graphics2D::begin()
  {
    setColor(WHITE);
    clear();
  }

  void Graphics2D::clear()
  {
    clear(0);
  }

  void Graphics2D::clear(uint8_t c) {
    buffer->reset(c);
  }

  void Graphics2D::pixel(uint8_t x, uint8_t y)
  {
    buffer->set(x, y, foregroundColor);
  }

  void Graphics2D::drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
    uint8_t steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
      swap(x0, y0);
      swap(x1, y1);
    }

    if (x0 > x1) {
      swap(x0, x1);
      swap(y0, y1);
    }

    uint8_t dx, dy;
    dx = x1 - x0;
    dy = abs(y1 - y0);

    int8_t err = dx / 2;
    int8_t ystep;

    if (y0 < y1) {
      ystep = 1;
    } else {
      ystep = -1;}

    for (; x0<x1; x0++) {
      if (steep) {
        pixel(y0, x0);
      } else {
        pixel(x0, y0);
      }
      err -= dy;
      if (err < 0) {
        y0 += ystep;
        err += dx;
      }
    }
  }
/*
  void Graphics2D::drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) 
  {
    uint8_t steep = ABS(y1 - y0) > ABS(x1 - x0);
    if (steep) 
    {
      SWAP(x0, y0);
      SWAP(x1, y1);
    }

    if (x0 > x1) 
    {
      SWAP(x0, x1);
      SWAP(y0, y1);
    }

    uint8_t dx, dy;
    dx = x1 - x0;
    dy = ABS(y1 - y0);

    int8_t err = dx / 2;
    int8_t ystep;

    ystep = y0 < y1 ? 1 : -1;

    for ( ; x0 < x1 ; ++x0) 
    {
      if (steep) 
      {
        pixel(y0, x0);
      }
      else 
      {
        pixel(x0, y0);
      }
      err -= dy;
      if (err < 0) 
      {
        y0 += ystep;
        err += dx;
      }
    }
  }
  */

  void Graphics2D::drawVerticalLine(uint8_t x, uint8_t y, uint8_t len)
  {
    drawLine(x, y, x , y + len);
  }

  void Graphics2D::drawHorizontalLine(uint8_t x, uint8_t y, uint8_t len)
  {
    drawLine(x, y, x + len , y);
  }

  void Graphics2D::drawRectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height) 
  {
    drawHorizontalLine(x, y, width);
    drawHorizontalLine(x, y + height, width);
    drawVerticalLine(x, y, height);
    drawVerticalLine(x + width, y, height);
  }

  void Graphics2D::fillRectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height)
  {
    for (uint8_t i = x; i < x + width ; i++) drawVerticalLine(i, y, height);
  }

  void Graphics2D::drawCircle(uint8_t xc, uint8_t yc, uint8_t radius)
  {
    int8_t f = 1 - radius;
    int8_t ddF_x = 1;
    int8_t ddF_y = -2 * radius;
    int8_t x = 0;
    int8_t y = radius;

    pixel(xc, yc + radius);
    pixel(xc, yc - radius);
    pixel(xc + radius, yc);
    pixel(xc - radius, yc);

    while (x < y) 
    {
      if (f >= 0) 
      {
        y--;
        ddF_y += 2;
        f += ddF_y;
      }
      x++;
      ddF_x += 2;
      f += ddF_x;

      pixel(xc + x, yc + y);
      pixel(xc - x, yc + y);
      pixel(xc + x, yc - y);
      pixel(xc - x, yc - y);

      pixel(xc + y, yc + x);
      pixel(xc - y, yc + x);
      pixel(xc + y, yc - x);
      pixel(xc - y, yc - x);
    }
  }

  void Graphics2D::fillCircle(uint8_t xc, uint8_t yc, uint8_t radius) 
  {
    int8_t f = 1 - radius;
    int8_t ddF_x = 1;
    int8_t ddF_y = -2 * radius;
    int8_t x = 0;
    int8_t y = radius;

    for (uint8_t i = yc - radius; i <= yc + radius; i++) 
    {
      pixel(xc, i);
    }

    while (x < y) 
    {
      if (f >= 0) 
      {
        y--;
        ddF_y += 2;
        f += ddF_y;
      }
      x++;
      ddF_x += 2;
      f += ddF_x;

      for (uint8_t i = yc - y ; i <= yc + y ; i++)
      {
        pixel(xc + x, i);
        pixel(xc - x, i);
      }
      for (uint8_t i = yc - x; i <= yc + x; i++)
      {
        pixel(xc + y, i);
        pixel(xc - y, i);
      }
    }
  }

  uint8_t Graphics2D::height()
  {
    return buffer->height;
  }

  uint8_t Graphics2D::width()
  {
    return buffer->width;
  }

  void Graphics2D::setColor(uint8_t color)
  {
    foregroundColor = color;
  }

  void Graphics2D::setBitmap(uint8_t* pixels, uint8_t page, uint8_t col, uint8_t pages, uint8_t cols)
  {
    for (uint8_t sp = 0, tp = page ; sp < pages ; ++sp, ++tp)
    {
      for (uint8_t sc = 0, tc = col ; sc < cols ; ++sc, ++tc)
      {
        buffer->setByte(tp, tc, pixels[sp * cols + sc]);
      }
    }
  }
  
  //#define _DEBUG_
  void Graphics2D::drawBitmap(uint8_t* pixels, uint8_t x, uint8_t y, uint8_t width, uint8_t height)
  {
    uint8_t numPages = height / 8;
    uint8_t pageOffset = y / 8;
    uint8_t bitOffset = y % 8;
    uint8_t colOffset = x;
    uint8_t current;
    for (uint8_t page = 0 ; page < numPages + 1 ; ++page)
    {
      for (uint8_t col = 0 ; col < width ; ++col)
      {
        #ifdef _DEBUG_
        Serial.print("page:");
        Serial.print(page);
        Serial.print(' ');
        Serial.print("col:");
        Serial.print(col);
        Serial.print(' ');
        Serial.print("current:");
        Serial.print(current);
        Serial.print(' ');
        #endif
        if (page > 0 && page < numPages)
          current = 0;
        else
        {
          buffer->getByte(pageOffset + page, colOffset + col, current);
          if (page == 0)
            current &= ~(0xFF << bitOffset);
          else if (page == numPages)
            current &= ~(0xFF << (8-bitOffset));
        }
        #ifdef _DEBUG_
        Serial.print(current);
        Serial.print(' ');
        #endif
        if (page < numPages)
          current |= pixels[page * width + col] << bitOffset;
        #ifdef _DEBUG_
        Serial.print(current);
        Serial.print(' ');
        #endif
        if (page > 0)
          current |= pixels[(page - 1) * width + col] >> (8-bitOffset);
        buffer->setByte(pageOffset + page, colOffset + col, current);
        #ifdef _DEBUG_
        Serial.print(current);
        Serial.print(' ');
        #endif
        #ifdef _DEBUG_
        Serial.println();
        #endif
      }
    }
  }

  void Graphics2D::clearBitmap(uint8_t* pixels, uint8_t x, uint8_t y, uint8_t width, uint8_t height)
  {
    uint8_t numPages = height / 8;
    uint8_t pageOffset = y / 8;
    uint8_t bitOffset = y % 8;
    uint8_t colOffset = x;
    uint8_t current;
    for (uint8_t page = 0 ; page < numPages + 1 ; ++page)
    {
      for (uint8_t col = 0 ; col < width ; ++col)
      {
        if (page > 0 && page < numPages)
          current = 0;
        else
        {
          buffer->getByte(pageOffset + page, colOffset + col, current);
          if (page == 0)
            current &= ~(0xFF << bitOffset);
          else if (page == numPages)
            current &= ~(0xFF << (8-bitOffset));
        }
        buffer->setByte(pageOffset + page, colOffset + col, current);
      }
    }
  }
  
}
