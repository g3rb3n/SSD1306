#include "SSD1306I2C128x64.h"

#include "screenbuffer/ByteUpdateScreenBuffer.h"
namespace g3rb3n
{
  SSD1306I2C128x64::SSD1306I2C128x64(uint8_t addr)
  :
    CommandDataIO(new I2CBus(addr)),
    SSD1306Driver(this),
    GraphicsPrint(new ByteUpdateScreenBuffer(128, 64, 1), new Fixed8x5())
  {
  }

  void SSD1306I2C128x64::begin()
  {
    //CommandDataIO::begin();
    SSD1306Driver::begin();
    GraphicsPrint::begin();
    this->setLayout(0, 0, 128, 8);
  }

  void SSD1306I2C128x64::display()
  {
    buffer->display(*this);
  }
  
}
