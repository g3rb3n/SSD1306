#ifndef _IOBus_H_
#define _IOBus_H_

#include <inttypes.h>

/** 
 * The IOBus class provides a generic interface for SPI / I2C / Parallel.
 */
namespace g3rb3n
{

  class IOBus;

  class IOBus 
  {
    public:
      virtual void write(uint8_t code, uint8_t data) const = 0;
      virtual void write(uint8_t code, uint8_t* data, uint16_t len) const;
      virtual void read(uint8_t code, uint8_t& data) const = 0;
      virtual void read(uint8_t code, uint8_t* data, uint16_t len) const = 0;
  };

}

#endif
