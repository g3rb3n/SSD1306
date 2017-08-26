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
      diff[i] = 0xFF;
  }

  PartialUpdateScreenBuffer::~PartialUpdateScreenBuffer()
  {
  }
  
  uint16_t PartialUpdateScreenBuffer::find(uint16_t pos, uint8_t value)
  {
    uint16_t i;
    for (i = pos ; i < size ; ++i)
    {
      if ( ( (diff[i / 8] >> (i % 8)  ) & 0x01) == value )
        break;
    }
    return i;
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

    uint16_t start, end;
    for (uint16_t i = 0 ; i < size ; )
    {
      start = find(i, 0x01);
      end = find(start, 0x00);
      #ifdef DEBUG
      Serial.print("start:");
      Serial.println(start);
      Serial.print("end:");
      Serial.println(end);
      #endif
      if (end > start)
      {
        bw.writeBufferBytes(start, buffer, end - start);
      }
      i = end;
    }
    
/*
    for (uint16_t i = 0 ; i < size ; ++i)
    {
      if (  diff[i / 8] & ( 0x01 << (i % 8) )  )
        bw.writeBufferByte(i, buffer[i]);
    }
*/
    for (uint8_t i = 0 ; i < diffSize ; ++i)
      diff[i] = 0;
  }

  void PartialUpdateScreenBuffer::setDiff(uint16_t pos)
  {
    uint8_t byte = pos / 8;
    uint8_t bit = pos % 8;
    diff[byte] |= (0x01 << bit);
  }
  
  void PartialUpdateScreenBuffer::setByte(uint8_t row, uint8_t col, uint8_t byte)
  {
    if (offScreen(col, row*8)) return;

    setDiff(row * 128 + col);
    ScreenBuffer::setByte(row, col, byte);
  }

  void PartialUpdateScreenBuffer::set(uint8_t x, uint8_t y, Pixel pixel)
  {
    if (offScreen(x,y)) return;

    setDiff(y / 8 * 128 + x);
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
