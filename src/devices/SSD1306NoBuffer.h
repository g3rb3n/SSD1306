#ifndef _SSD1306NoBuffer_H_
#define _SSD1306NoBuffer_H_

#include "io/IOBus.h"
#include "io/CommandDataIO.h"
#include "screenmap/SSD1306ScreenControl.h"
#include "screenmap/DirectWriteScreenMap.h"
#include "driver/SSD1306Driver.h"

namespace g3rb3n
{

  class SSD1306NoBuffer 
  :
  public CommandDataIO, 
  public SSD1306Driver, 
  public SSD1306ScreenControl, 
  public DirectWriteScreenMap
  {
    public:
      SSD1306NoBuffer(IOBus* io);
      
      void begin();
      void setLayout(uint8_t p, uint8_t c, uint8_t pc, uint8_t cc);
    private:
      IOBus* io;
  };
  
}

#endif
