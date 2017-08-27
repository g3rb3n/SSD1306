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
      uint8_t pages = 8;
      uint8_t columns = 128;
      uint8_t pageOffset = 0;
      uint8_t columnOffset = 0;

    public:
      SSD1306ScreenControl();
      SSD1306ScreenControl(CommandDataIO* bus);
      SSD1306ScreenControl(CommandDataIO* _io, 
        uint8_t _pages, uint8_t _colums, 
        uint8_t _pageOffset, uint8_t _columnOffset);
      ~SSD1306ScreenControl();
      
      void setLayout(uint8_t _pages, uint8_t _colums, uint8_t _pageOffset, uint8_t _columnOffset);
      void setPageColumnMode(uint16_t startPage, uint16_t startColumn, uint16_t pages, uint16_t columns);
  };
  
}

#endif
