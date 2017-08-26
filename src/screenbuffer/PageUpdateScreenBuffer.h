#ifndef _PageUpdateScreenBuffer_H_
#define _PageUpdateScreenBuffer_H_

#include "ScreenBuffer.h"

namespace g3rb3n
{

  class PageUpdateScreenBuffer : public ScreenBuffer
  {
    public:

    private:
      uint8_t diff;

    public:
      PageUpdateScreenBuffer(uint8_t width, uint8_t height, uint8_t depth);
      ~PageUpdateScreenBuffer();

      void setByte(uint8_t row, uint8_t col, uint8_t byte) override;
      void set(uint8_t x, uint8_t y, Pixel pixel) override;

      void display(BufferWriter& bw) override;

  };

}
#endif
