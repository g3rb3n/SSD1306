#ifndef _I2CIO_H_
#define _I2CIO_H_

#include "ByteIO.h"
#include <inttypes.h>

#include <Wire.h>

#define I2C_FREQ 400000L	// I2C Frequency is 400kHz (fast as possible)

#ifdef ARDUINO_ARCH_ESP8266
  #define PINS_ON_BEGIN
#elif ARDUINO_ARCH_AVR
  #define PINS_ON_PROPERTIES
#else
  #warning "No support for setting SDL and SDA pins"
#endif

namespace g3rb3n
{

  class I2CIO : public ByteIO
  {
    private:
      uint8_t _address;

    public:
      I2CIO(uint8_t address);
      I2CIO(uint8_t address, uint8_t sda, uint8_t cls);
      ~I2CIO();

      uint8_t address() const;
      
      uint8_t write(uint8_t reg, uint8_t data) const;
      uint8_t read(uint8_t reg, uint8_t& data) const;
  };

}
#endif
