#include "ScreenBuffer.h"
#include <inttypes.h>

namespace g3rb3n
{
  
  ScreenBuffer::ScreenBuffer(uint8_t _width, uint8_t _height, uint8_t _depth):
    width(_width),
    height(_height),
    depth(_depth),
    size(_width * _height / 8),
    buffer(new uint8_t[_width * _height / 8])
  {
    
  }

  ScreenBuffer::~ScreenBuffer()
  {
  }

  void ScreenBuffer::begin()
  {}


  void ScreenBuffer::set(uint8_t x, uint8_t y, Pixel pixel)
  {
    if (offScreen(x,y)) return;

    buffer[x + (y / 8) * width] &= ~(0x01 << (y % 8));
    buffer[x + (y / 8) * width] |=  (pixel << (y % 8));
  }

  void ScreenBuffer::get(uint8_t x, uint8_t y, Pixel& pixel)
  {
    if (offScreen(x,y)) return;

    pixel = buffer[x + (y / 8) * width] & 0x01 << (y % 8);
  }

  bool ScreenBuffer::offScreen(uint8_t x, uint8_t y)
  {
    return x < 0 || x >= width ||
           y < 0 || y >= height;
  }
  
  void ScreenBuffer::reset()
  {
    reset(0);
  }

  void ScreenBuffer::reset(Pixel pixel)
  {
    memset(buffer, pixel, size);
  }

  void ScreenBuffer::display(BufferWriter& bw)
  {
    Serial.println("ScreenBuffer::display");
    for (uint16_t i = 0 ; i < size ; ++i)
    {
      bw.writeBufferByte(i, buffer[i]);
    }
  }
/*
  void ScreenBuffer::write(SSD1306* ssd)
  {
    uint8_t i, j;

    for (i = 0 ; i < pages ; ++i)
    {
      ssd->setPageAddress(i);
      ssd->setColumnAddress(0);
      for (j = 0 ; j < columns ; j++)
      {
        ssd->data(buffer[ i * columns + j ]);
      }
    }
  }
*/
  uint8_t* ScreenBuffer::screenBuffer()
  {
    return buffer;
  }
}
