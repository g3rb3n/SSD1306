#ifndef _ScreenBuffer_H_
#define _ScreenBuffer_H_

#include "BufferWriter.h"
#include "../util/types.h"

#define Pixel uint8_t

namespace g3rb3n
{

  class ScreenBuffer
  {
    public:
      const uint8_t width;
      const uint8_t height;
      const uint16_t size;

    protected:
      uint8_t pages;
      uint8_t columns;
      uint8_t depth;
      uint8_t* buffer;

    public:
      ScreenBuffer(uint8_t width, uint8_t height, uint8_t depth);
      ~ScreenBuffer();

      void begin();
      
      virtual void set(uint8_t x, uint8_t y, Pixel pixel);
      virtual void setByte(uint8_t row, uint8_t col, uint8_t byte);
      void get(uint8_t x, uint8_t y, Pixel& pixel);
      void getByte(uint8_t row, uint8_t col, Pixel& pixel);
      bool offScreen(uint8_t x, uint8_t y);

      virtual void reset(Pixel data);
      virtual void reset();

      virtual void display(BufferWriter& bw);

      uint8_t* screenBuffer();
//      void write(SSD1306* ssd);
  };

}

#endif
