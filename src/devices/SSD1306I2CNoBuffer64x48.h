#ifndef _SSD1306I2CNoBuffer64x48_H_
#define _SSD1306I2CNoBuffer64x48_H_

#include "io/I2CBus.h"
#include "io/CommandDataIO.h"
#include "screenmap/SSD1306ScreenControl.h"
#include "screenmap/DirectWriteScreenMap.h"
#include "driver/SSD1306Driver.h"

namespace g3rb3n
{

  class SSD1306I2CNoBuffer64x48 
  :
  public CommandDataIO, 
  public SSD1306Driver, 
  public SSD1306ScreenControl, 
  public DirectWriteScreenMap
  {
    public:
      SSD1306I2CNoBuffer64x48(uint8_t addr);
      
      void begin();
  };
  
}

#endif
