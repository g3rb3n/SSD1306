#ifndef _GraphicsPrint_H_
#define _GraphicsPrint_H_

#include <Print.h>

#include "Graphics2D.h"
#include "../fonts/Fixed.h"
#include "../util/types.h"

namespace g3rb3n
{

  class GraphicsPrint : public Graphics2D, public Print
  {
    private:
      Fixed* font;
      uint8_t x;
      uint8_t y;
      
    public:
      GraphicsPrint(ScreenBuffer* screen, Fixed* font);
      ~GraphicsPrint();

      virtual size_t write(uint8_t);

      void begin(void);
      
      void setCursor(uint8_t r, uint8_t c);
      void setOffset(uint8_t x, uint8_t y);

    private:
      void drawChar(uint8_t x, uint8_t y, uint8_t character);
      void setChar(uint8_t row, uint8_t col, uint8_t character);
      void drawCharByPixels(uint8_t x, uint8_t y, uint8_t c);
    };

}

#endif
