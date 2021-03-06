#include "PageUpdateScreenBuffer.h"

namespace g3rb3n
{
  
  PageUpdateScreenBuffer::PageUpdateScreenBuffer(uint8_t _width, uint8_t _height, uint8_t _depth)
  :
    ScreenBuffer(_width, _height, _depth)
  {
    diff = 0;
  }

  PageUpdateScreenBuffer::~PageUpdateScreenBuffer()
  {
  }

  void PageUpdateScreenBuffer::display(BufferWriter& bw)
  {
    for (uint8_t page = 0 ; page < pages ; ++page)
    {
      if ( !(diff & (0x01 << page)))
      {
        continue;
      }
      bw.writeBufferBytes(page*columns, buffer, columns);
/*
      uint16_t start = page * columns;
      uint16_t end = start + columns;
      for (uint16_t i = start; i < end ; ++i)
      {
          bw.writeBufferByte(i, buffer[i]);
      }
      */
    }
    diff = 0x00;
  }

  void PageUpdateScreenBuffer::setByte(uint8_t row, uint8_t col, uint8_t byte)
  {
    if (offScreen(col, row*8)) return;

    diff |= (0x01 << row);
    ScreenBuffer::setByte(row, col, byte);
  }

  void PageUpdateScreenBuffer::set(uint8_t x, uint8_t y, Pixel pixel)
  {
    if (offScreen(x,y)) return;

    uint8_t page = y / 8;
    diff |= (0x01 << page);
    ScreenBuffer::set(x, y, pixel);
  }
}
