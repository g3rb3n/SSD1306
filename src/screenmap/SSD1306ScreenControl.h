#ifndef _ScreenMap_H_
#define _ScreenMap_H_

#include "ScreenControl.h"
#include "../io/CommandDataIO.h"

namespace g3rb3n
{

  class SSD1306ScreenControl : public ScreenControl
  {
    private:
      CommandDataIO* io;

    public:
      SSD1306ScreenControl();
      SSD1306ScreenControl(CommandDataIO* bus);
      ~SSD1306ScreenControl();
      
      void setPageColumnMode(uint16_t startPage, uint16_t startColumn, uint16_t pages, uint16_t columns);
  };
  
}

#endif
