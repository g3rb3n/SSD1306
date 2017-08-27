#ifndef _SSD1306I2C_H_
#define _SSD1306I2C_H_

#include "io/I2CBus.h"
#include "io/CommandDataIO.h"
#include "driver/SSD1306Driver.h"
#include "gfx/GraphicsPrint.h"
#include "fonts/Fixed8x5.h"

namespace g3rb3n
{

  class SSD1306I2C 
  :
  public CommandDataIO, 
  public SSD1306Driver, 
  public GraphicsPrint
  {
    public:
      SSD1306I2C(uint8_t addr);
      SSD1306I2C(uint8_t addr, uint8_t width, uint8_t height);
      
      void begin();
      void display();
  };
  
}

#endif
