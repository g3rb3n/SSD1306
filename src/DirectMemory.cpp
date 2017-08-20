#include "DirectMemory.h"
#include <inttypes.h>

#ifndef _BV
#define _BV(x) (1<<x)
#endif

#define I2C_COMMAND 0x00
#define I2C_DATA 0x40

namespace g3rb3n
{
  
  DirectMemory::DirectMemory(ByteIO* _byteIO, uint8_t _width, uint8_t _height, uint8_t _depth):
    byteIO(_byteIO),
    width(_width),
    height(_height),
    depth(_depth),
    size(_width * _height / 8)
  {
    
  }

  DirectMemory::~DirectMemory()
  {
    //TODO : cleanup
  }

  uint8_t DirectMemory::write(uint8_t x, uint8_t y, uint8_t pixel)
  {
    uint16_t pos = 128 * x + y / 8;
    write(pos, pixel);
  }

  uint8_t DirectMemory::write(uint16_t pos, uint8_t d)
  {
    uint8_t page = pos / 128;
    uint8_t col = pos % 128;
    setPageAddress(page);
    setColumnAddress(col);
    data(d);
  }

  uint8_t DirectMemory::write(uint8_t pixel)
  {
    uint8_t i, j;

    for (i = 0 ; i < 8 ; i++)
    {
      setPageAddress(i);
      setColumnAddress(0);
      for ( j = 0 ; j < 0x40 ; j++)
      {
        data(pixel);
      }
    }
  }

  uint8_t DirectMemory::_xor(uint8_t x, uint8_t y)
  {
  }

  uint8_t DirectMemory::_or(uint8_t x, uint8_t y)
  {
  }

  uint8_t DirectMemory::_and(uint8_t x, uint8_t y)
  {
  }

  void DirectMemory::setPageAddress(uint8_t add) {
  	add=0xb0|add;
  	command(add);
  	return;
  }

  /** \brief Set SSD1306 column address.

      Send column address command and address to the SSD1306 OLED controller.
  */
  void DirectMemory::setColumnAddress(uint8_t add) {
  	command((0x10|(add>>4))+0x02);
  	command((0x0f&add));
  	return;
  }
  
  void DirectMemory::command(uint8_t c)
  {
    byteIO->write(I2C_COMMAND, c);
  }

  
  void DirectMemory::data(uint8_t c)
  {
    byteIO->write(I2C_DATA, c);
  }
  
  uint8_t DirectMemory::display()
  {
  }
}
