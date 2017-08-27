#include "SSD1306I2C.h"

#include "screenbuffer/ByteUpdateScreenBuffer.h"
namespace g3rb3n
{
  SSD1306I2C::SSD1306I2C(uint8_t addr)
  :
    CommandDataIO(new I2CBus(0x3C)),
    SSD1306Driver(this),
    GraphicsPrint(new ByteUpdateScreenBuffer(128, 64, 1), new Fixed8x5())
  {
  }

  SSD1306I2C::SSD1306I2C(uint8_t addr, uint8_t width, uint8_t height)
  :
    CommandDataIO(new I2CBus(0x3C)),
    SSD1306Driver(this),
    GraphicsPrint(new ByteUpdateScreenBuffer(width, height, 1), new Fixed8x5())
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
