#include "ScreenBuffer.h"

#include <string.h> //For memset

namespace g3rb3n
{
  
  ScreenBuffer::ScreenBuffer(uint8_t _width, uint8_t _height, uint8_t _depth):
    width(_width),
    height(_height),
    depth(_depth),
    size(_width * _height / 8),
    pages(_height / 8),
    columns(_width),
    buffer(new uint8_t[_width * _height / 8])
  {
    
  }

  ScreenBuffer::~ScreenBuffer()
  {
  }

  uint8_t* ScreenBuffer::_buffer()
  {
    return buffer;
  }
  
  void ScreenBuffer::begin()
  {}

  void ScreenBuffer::set(uint8_t x, uint8_t y, Pixel pixel)
  {
    if (offScreen(x,y)) return;

    buffer[x + (y / 8) * width] &= ~(0x01 << (y % 8));
    buffer[x + (y / 8) * width] |=  (pixel << (y % 8));
  }

  void ScreenBuffer::setByte(uint8_t row, uint8_t col, uint8_t byte)
  {
    buffer[row * width + col] = byte;
  }

  void ScreenBuffer::getByte(uint8_t row, uint8_t col, uint8_t& byte)
  {
    byte = buffer[row * width + col];
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
    //Serial.println("ScreenBuffer::display");
    bw.writeBufferBytes(0, buffer, size);
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
