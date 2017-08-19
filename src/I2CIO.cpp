#include "I2CIO.h"

#include <Arduino.h>

namespace g3rb3n
{
  
  I2CIO::I2CIO(uint8_t address):
    _address(address)
  {
    Wire.begin();
  }

  I2CIO::I2CIO(uint8_t address, uint8_t sda, uint8_t scl):
    _address(address)
  {
    #ifdef PINS_ON_PROPERTIES
        Wire.scl_pin = scl;
        Wire.sda_pin = sda;
        Wire.begin();
    #endif
    #ifdef PINS_ON_BEGIN
        Wire.begin(scl, sda);
    #endif
    #ifdef NO_PINS
      Wire.begin();
    #endif
  }

  I2CIO::~I2CIO()
  {}

  uint8_t I2CIO::address() const
  {
    return _address;
  }
  
  uint8_t I2CIO::write(uint8_t reg, uint8_t data) const
  {
//    Serial.print("I2C:");
//    Serial.print(_address, HEX);
//    Serial.print(":");
//    Serial.print(reg, HEX);
//    Serial.print(":");
//    Serial.print(data, HEX);
//    Serial.println();
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission();
 //   delay(10);
    return 0;
  }

  uint8_t I2CIO::read(uint8_t reg, uint8_t& data) const
  {
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom(_address, (uint8_t) 1);
    data = Wire.read();
    return 0;
  }


}
