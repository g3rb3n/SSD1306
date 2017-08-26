#include "CommandDataIO.h"

#include <Arduino.h>

#define BUS_COMMAND 0x00
#define BUS_DATA 0x40

namespace g3rb3n
{

  CommandDataIO::CommandDataIO()
  {}

  CommandDataIO::CommandDataIO(IOBus* _iobus)
  :
  iobus(_iobus)
  {}

  CommandDataIO::~CommandDataIO()
  {}
  
  /** 
   * Send a command to the OLED display.
   */
  void CommandDataIO::command(uint8_t c) const
  {
    #ifdef DEBUG
    Serial.println("CommandDataIO::command");
    Serial.print("0x");
    Serial.print(c, 16);
    Serial.println();
    #endif
    iobus->write(BUS_COMMAND, c);
  }

  /**
   * Send a data byte to the OLED display.
   */
  void CommandDataIO::data(uint8_t c) const
  {
    iobus->write(BUS_DATA, c);
  }

  /**
   * Send a data byte to the OLED display.
   */
  void CommandDataIO::command(uint8_t* c, uint16_t len) const
  {
    #ifdef DEBUG
    Serial.println("CommandDataIO::command");
    for (int i = 0 ; i < len ; ++i)
    {
      Serial.print("0x");
      Serial.print(c[i], 16);
      Serial.print(' ');
    }
    #endif
    Serial.println();
    iobus->write(BUS_COMMAND, c, len);
  }

  /**
   * Send a data byte to the OLED display.
   */
  void CommandDataIO::data(uint8_t* c, uint16_t len) const
  {
    iobus->write(BUS_DATA, c, len);
  }
  
}
