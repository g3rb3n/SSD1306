#include "SSD1306I2C64x48.h"

#include "screenbuffer/ByteUpdateScreenBuffer.h"
namespace g3rb3n
{
  SSD1306I2C64x48::SSD1306I2C64x48(uint8_t addr)
  :
    CommandDataIO(new I2CBus(addr)),
    SSD1306Driver(this),
    GraphicsPrint(new ByteUpdateScreenBuffer(64, 48, 1), new Fixed8x5())
  {
  }

  void SSD1306I2C64x48::begin()
  {
    //CommandDataIO::begin();
    SSD1306Driver::begin();
    GraphicsPrint::begin();
    this->setLayout(32, 0, 64, 6);
  }

  void SSD1306I2C64x48::display()
  {
    buffer->display(*this);
  }
  
}
