#include "BufferedMemory.h"
#include <inttypes.h>

// This fixed ugly GCC warning "only initialized variables can be placed into program memory area"
#if defined(__AVR__)
#undef PROGMEM
#define PROGMEM __attribute__((section(".progmem.data")))
#endif

#ifndef _BV
#define _BV(x) (1<<x)
#endif

#define I2C_COMMAND 0x00
#define I2C_DATA 0x40

namespace g3rb3n
{
  
  BufferedMemory::BufferedMemory(ByteIO* _byteIO, uint8_t _width, uint8_t _height, uint8_t _depth):
    byteIO(_byteIO),
    width(_width),
    height(_height),
    depth(_depth),
    size(_width * _height / 8),
    buffer(new uint8_t[_width * _height / 8])
  {
    
  }

  BufferedMemory::~BufferedMemory()
  {
    //TODO : cleanup
  }

  uint8_t BufferedMemory::write(uint8_t x, uint8_t y, uint8_t pixel)
  {
    
  }

  uint8_t BufferedMemory::write(uint16_t pos, uint8_t pixel)
  {
    
  }

  uint8_t BufferedMemory::write(uint8_t pixel)
  {
    memset(buffer, pixel, size);
  }

  uint8_t BufferedMemory::_xor(uint8_t x, uint8_t y)
  {
    buffer[x + (y / 8) * width] ^= _BV((y % 8));
  }

  uint8_t BufferedMemory::_or(uint8_t x, uint8_t y)
  {
    buffer[x + (y / 8) * width] |= _BV((y % 8));
  }

  uint8_t BufferedMemory::_and(uint8_t x, uint8_t y)
  {
    buffer[x + (y / 8) * width] &= ~_BV((y % 8));
  }

  void BufferedMemory::setPageAddress(uint8_t add) {
  	add=0xb0|add;
  	command(add);
  	return;
  }

  /** \brief Set SSD1306 column address.

      Send column address command and address to the SSD1306 OLED controller.
  */
  void BufferedMemory::setColumnAddress(uint8_t add) {
  	command((0x10|(add>>4))+0x02);
  	command((0x0f&add));
  	return;
  }
  
  void BufferedMemory::command(uint8_t c)
  {
    byteIO->write(I2C_COMMAND, c);
  }

  
  void BufferedMemory::data(uint8_t c)
  {
    byteIO->write(I2C_DATA, c);
  }
  
  uint8_t BufferedMemory::display()
  {
    uint8_t i, j;

    for (i=0; i<6; i++) {
      setPageAddress(i);
      setColumnAddress(0);
      for (j=0;j<0x40;j++) {
        data(buffer[i*0x40+j]);
      }
    }
  }
}
