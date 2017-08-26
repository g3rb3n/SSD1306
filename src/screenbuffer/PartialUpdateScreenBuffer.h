#ifndef _PartialUpdateScreenBuffer_H_
#define _PartialUpdateScreenBuffer_H_

#include "ScreenBuffer.h"

namespace g3rb3n
{

  class PartialUpdateScreenBuffer : public ScreenBuffer
  {
    public:

    private:
      uint8_t* diff;
      uint8_t diffSize;

    public:
      PartialUpdateScreenBuffer(uint8_t width, uint8_t height, uint8_t depth);
      ~PartialUpdateScreenBuffer();

      void setByte(uint8_t row, uint8_t col, uint8_t byte) override;
      void set(uint8_t x, uint8_t y, Pixel pixel) override;

      void reset(Pixel data) override;
      void reset() override;
      
      void display(BufferWriter& bw) override;
      
    private:
      uint16_t find(uint16_t pos, uint8_t value);
      void setDiff(uint16_t pos);


  };

}
#endif
