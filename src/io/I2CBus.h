#ifndef _I2CBus_H_
#define _I2CBus_H_

#include "io/IOBus.h"

namespace g3rb3n
{

  class I2CBus : public IOBus
  {
    private:
      uint8_t _address;

    public:
      I2CBus(uint8_t address);
      I2CBus(uint8_t address, uint8_t sda, uint8_t cls);
      ~I2CBus();

      uint8_t address() const;
      
      void write(uint8_t reg, uint8_t data) const;
      void write(uint8_t reg, uint8_t* data, uint16_t len) const;
      void read(uint8_t reg, uint8_t& data) const;
      void read(uint8_t reg, uint8_t* data, uint16_t len) const;
  };

}
#endif
