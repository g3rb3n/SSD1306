#ifndef _SPIBus_H
#define _SPIBus_H

#include "io/IOBus.h"

namespace g3rb3n
{

  class SPIBus : public IOBus
  {
    private:
      uint8_t _address;
      uint8_t resPin;
      uint8_t dcPin;
      uint8_t csPin;
    public:
      //SPIBus();
      SPIBus(uint8_t res, uint8_t dc, uint8_t cs);
      ~SPIBus();
      
      void write(uint8_t reg, uint8_t data) const;
      void write(uint8_t reg, uint8_t* data, uint16_t len) const;
      void read(uint8_t reg, uint8_t& data) const;
      void read(uint8_t reg, uint8_t* data, uint16_t len) const;
  };

}
#endif
