#ifndef _SSD1306_H_
#define _SSD1306_H_

#include "io/IOBus.h"
#include "io/CommandDataIO.h"
#include "driver/SSD1306Driver.h"
#include "screenbuffer/ScreenBuffer.h"
#include "gfx/GraphicsPrint.h"
#include "fonts/Fixed.h"

namespace g3rb3n
{

  class SSD1306 
  :
  public CommandDataIO, 
  public SSD1306Driver, 
  public GraphicsPrint
  {
    public:
      SSD1306(IOBus* bus, ScreenBuffer* buffer);
      SSD1306(IOBus* bus, ScreenBuffer* buffer, Fixed* font);
      
      void begin();
      void display();
  };
  
}

#endif
