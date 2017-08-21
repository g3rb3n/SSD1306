#include "PartialUpdateScreenBuffer.h"

namespace g3rb3n
{
  
  PartialUpdateScreenBuffer::PartialUpdateScreenBuffer(uint8_t _width, uint8_t _height, uint8_t _depth)
  :
  ScreenBuffer(_width, _height, _depth),
  diffSize( (size + 7) / 8 ),
  diff(new uint8_t[128])
  {
    for (uint8_t i = 0 ; i < diffSize ; ++i)
      diff[i] = 0;
  }

  PartialUpdateScreenBuffer::~PartialUpdateScreenBuffer()
  {
  }
  //#define DEBUG
  void PartialUpdateScreenBuffer::display(BufferWriter& bw)
  {
    //    Serial.println("PartialUpdateScreenBuffer::display");
    //    Serial.print("diffSize: ");
    //    Serial.println(diffSize);
    #ifdef DEBUG
    for (uint8_t i = 0 ; i < diffSize ; ++i)
    {
      Serial.print(diff[i], 16);
      Serial.print(' ');
      if (i % 16 == 15)
        Serial.println();
    }
    Serial.println();
    #endif
    for (uint16_t i = 0 ; i < size ; ++i)
    {
      if (  diff[i / 8] & ( 0x01 << (i % 8) )  )
        bw.writeBufferByte(i, buffer[i]);
    }
    for (uint8_t i = 0 ; i < diffSize ; ++i)
      diff[i] = 0;
  }

  void PartialUpdateScreenBuffer::set(uint8_t x, uint8_t y, Pixel pixel)
  {
    if (offScreen(x,y)) return;
//    Serial.println("PartialUpdateScreenBuffer::set");

    uint16_t pos = (y / 8) * 128 + x;
    uint8_t byte = pos / 8;
    uint8_t bit = pos % 8;
//    Serial.print("byte: ");
//    Serial.println(byte);
    diff[byte] |= (0x01 << bit);
    ScreenBuffer::set(x, y, pixel);
  }
  
  void PartialUpdateScreenBuffer::reset(Pixel p)
  {
    for (uint16_t i = 0 ; i < size ; ++i)
    {
      if(buffer[i])
        diff[i / 8] |= (0x01 << (i % 8));
    }
//    for (uint8_t i = 0 ; i < diffSize ; ++i)
//      diff[i] = 0xFF;
    
    ScreenBuffer::reset(p);
  }

  void PartialUpdateScreenBuffer::reset()
  {
    ScreenBuffer::reset();
  }
}
