#ifndef _DIRECT_MEMORY_H_
#define _DIRECT_MEMORY_H_

#include "GraphicalMemory.h"
#include "ByteIO.h"
#include <inttypes.h>

namespace g3rb3n
{

  class DirectMemory : public GraphicalMemory
  {
    private:
      ByteIO* byteIO;
      uint8_t width;
      uint8_t height;
      uint8_t depth;
      uint16_t size;
      
    public:
      DirectMemory(ByteIO* byteIO, uint8_t width, uint8_t height, uint8_t depth);
      ~DirectMemory();
      
      uint8_t write(uint8_t x, uint8_t y, uint8_t pixel);
      uint8_t write(uint16_t pos, uint8_t data);
      uint8_t write(uint8_t data);

      uint8_t _xor(uint8_t x, uint8_t y);
      uint8_t _or(uint8_t x, uint8_t y);
      uint8_t _and(uint8_t x, uint8_t y);

      uint8_t display();
      
    private:
      void setPageAddress(uint8_t add);
      void setColumnAddress(uint8_t add);
      
      void command(uint8_t c);
      void data(uint8_t c);
  };

}
#endif
