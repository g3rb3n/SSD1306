#include "SSD1306I2C.h"

namespace g3rb3n
{
  SSD1306I2C::SSD1306I2C(uint8_t addr)
  :
    CommandDataIO(new I2CBus(0x3C)),
    SSD1306Driver(this),
    GraphicsPrint(new ScreenBuffer(128, 64, 1), new Fixed8x5())
  {
  }
  
  void SSD1306I2C::begin()
  {
    //CommandDataIO::begin();
    SSD1306Driver::begin();
    GraphicsPrint::begin();
  }

  void SSD1306I2C::display()
  {
    buffer->display(*this);
  }
  
}
