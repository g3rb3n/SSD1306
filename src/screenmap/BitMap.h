#ifndef _BitMap_H_
#define _BitMap_H_

#include <inttypes.h>

namespace g3rb3n
{

  class BitMap
  {
    private:
      uint8_t* buffer;
    public:
      uint16_t width;
      uint16_t height;
      
    public:
      BitMap(uint16_t width, uint16_t height);
      BitMap(uint8_t* buffer, uint16_t width, uint16_t height);

      uint8_t setByte(uint16_t pos, uint8_t byte);
      uint8_t getByte(uint16_t pos, uint8_t& byte);
      
      uint8_t* getBuffer();
  };

}
#endif

