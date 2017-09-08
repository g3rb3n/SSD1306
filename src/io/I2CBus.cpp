#include "I2CBus.h"
#include "I2CBus_hw.h"

#include <Arduino.h>
#include <Wire.h>

#define I2CBUS_COMMAND 0x00
#define I2CBUS_DATA 0x40

namespace g3rb3n
{
  
  I2CBus::I2CBus(uint8_t address):
    _address(address)
  {
    Wire.begin();
    //setFrequency(I2CBUS_FREQUENCY);
  }
  
  
  I2CBus::I2CBus(uint8_t address, uint32_t clock):
    _address(address)
  {
    Wire.begin();
    setFrequency(clock);
  }  

  I2CBus::I2CBus(uint8_t address, uint8_t sda, uint8_t scl):
    _address(address)
  {
    setPins(sda, scl);
    //setFrequency(I2CBUS_FREQUENCY);
  }

  I2CBus::I2CBus(uint8_t address, uint8_t sda, uint8_t scl, uint32_t freq):
    _address(address)
  {
    setPins(sda, scl);
    setFrequency(freq);
  }

  I2CBus::~I2CBus()
  {}

  void I2CBus::setFrequency(uint32_t freq)
  {
    #ifdef I2CBUS_FREQUENCY_BY_TWBR
      #error "Setting clock by TWBR is not implemented"
    #endif
    #ifdef I2CBUS_FREQUENCY_BY_FUNCTION_SET_CLOCK
      Wire.setClock(freq);
    #endif
    #ifdef I2CBUS_FREQUENCY_BY_FUNCTION_SET_FREQUENCY
      Wire.setFrequency(freq);
    #endif    
  }

  void I2CBus::setPins(uint8_t sda, uint8_t scl)
  {
    #ifdef I2CBUS_SET_PINS_ON_PROPERTIES
      Wire.scl_pin = scl;
      Wire.sda_pin = sda;
      Wire.begin();
    #endif
    #ifdef I2CBUS_SET_PINS_ON_BEGIN
        Wire.begin(scl, sda);
    #endif
    #ifdef I2CBUS_SET_PINS_NOT_IMPLEMENTED
      Wire.begin();
    #endif
  }
  
  uint8_t I2CBus::address() const
  {
    return _address;
  }
  
  void I2CBus::write(uint8_t reg, uint8_t data) const
  {
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission();
    //delay(10);
  }

  void I2CBus::write(uint8_t reg, uint8_t* data, uint16_t len) const
  {
    for (uint16_t i = 0; i < len;) 
    {
      Wire.beginTransmission(_address);
      Wire.write(reg);
      for (uint8_t x = 0; x < 16 && i < len; ++i, ++x) 
      {
        Wire.write(data[i]);
      }
      Wire.endTransmission();
    }
  }

  void I2CBus::read(uint8_t reg, uint8_t& data) const
  {
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom(_address, (uint8_t) 1);
    data = Wire.read();
  }

  void I2CBus::read(uint8_t reg, uint8_t* data, uint16_t len) const
  {
  }

}
