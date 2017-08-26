#include "SSD1306.h"

#include "fonts/Fixed8x5.h"

namespace g3rb3n
{
  SSD1306::SSD1306(IOBus* bus, ScreenBuffer* buffer)
  :
    CommandDataIO(bus),
    SSD1306Driver(this),
    GraphicsPrint(buffer, new Fixed8x5())
  {
  }

  SSD1306::SSD1306(IOBus* bus, ScreenBuffer* buffer, Fixed* font)
  :
    CommandDataIO(bus),
    SSD1306Driver(this),
    GraphicsPrint(buffer, font)
  {
  }

  void SSD1306::begin()
  {
    //CommandDataIO::begin();
    SSD1306Driver::begin();
    GraphicsPrint::begin();
  }

  void SSD1306::display()
  {
    buffer->display(*this);
  }
  
}
