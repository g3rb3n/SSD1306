#include "SPIBus.h"

#include <SPI.h>

SPISettings oledSettings(100000, MSBFIRST, SPI_MODE0);

#define SPIBUS_COMMAND 0x00
#define SPIBUS_DATA 0x40

namespace g3rb3n
{
  /*
  SPIBus::SPIBus()
  //:
  //  mosiPin(MOSI),
  //  sckPin(SCK),
  //  csPin(CS)
  {
  	SPI.begin();
  }
*/
  SPIBus::SPIBus(uint8_t res, uint8_t dc, uint8_t cs):
    resPin(res),
    dcPin(dc),
    csPin(cs)
  {
    pinMode(resPin, OUTPUT);	// MOSI is an OUTPUT
  	pinMode(dcPin, OUTPUT);	// SCK is an OUTPUT
  	pinMode(csPin, OUTPUT);	// CS is an OUTPUT
    digitalWrite(resPin, HIGH);	// Reset
    delay(10);
    digitalWrite(resPin, LOW);	// Reset
    delay(10);
    digitalWrite(resPin, HIGH);	// Reset
    delay(10);
  	digitalWrite(csPin, HIGH);	// Start CS High

    SPI.setClockDivider(SPI_CLOCK_DIV2);	// Fastest SPI clock possible
  	SPI.setDataMode(SPI_MODE0);	// CPOL=0 and CPHA=0, SPI mode 0
  #if defined(__AVR__)
  	pinMode(10, OUTPUT); // Required for setting into Master mode
  #endif
  	SPI.begin();    
  }

  SPIBus::~SPIBus()
  {}

  void SPIBus::write(uint8_t reg, uint8_t data) const
  {
    if (reg == SPIBUS_COMMAND)
      digitalWrite(dcPin, LOW);	// DC pin LOW for a command
		else
      digitalWrite(dcPin, HIGH);	// DC pin HIGH for data

    //SPI.beginTransaction(oledSettings);
  	digitalWrite(csPin, LOW);
  	SPI.transfer(data);
  	digitalWrite(csPin, HIGH);
  	//SPI.endTransaction();
    //delay(1);
  }

  void SPIBus::write(uint8_t reg, uint8_t* data, uint16_t len) const
  {
    for (uint16_t i = 0 ; i < len ; ++i)
      write(reg, data[i]);
  }

  void SPIBus::read(uint8_t reg, uint8_t& data) const
  {
  }

  void SPIBus::read(uint8_t reg, uint8_t* data, uint16_t len) const
  {
  }


}
