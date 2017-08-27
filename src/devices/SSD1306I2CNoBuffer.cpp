#include "SSD1306I2CNoBuffer.h"

namespace g3rb3n
{
  SSD1306I2CNoBuffer::SSD1306I2CNoBuffer(uint8_t addr)
  :
    CommandDataIO(new I2CBus(0x3C)),
    SSD1306Driver(this),
    SSD1306ScreenControl(this),
    DirectWriteScreenMap(this, this)
  {
  }
  
  void SSD1306I2CNoBuffer::begin()
  {
    //CommandDataIO::begin();
    SSD1306Driver::begin();
    //DirectWriteScreenMap::begin();
  }

  void SSD1306I2CNoBuffer::setLayout(uint8_t p, uint8_t c, uint8_t pc, uint8_t cc)
  {
    SSD1306Driver::setLayout(p, c, pc, cc);
    SSD1306ScreenControl::setLayout(p, c, pc, cc);
  }
}
