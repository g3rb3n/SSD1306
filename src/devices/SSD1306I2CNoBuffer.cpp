#include "SSD1306I2CNoBuffer.h"

namespace g3rb3n
{
  SSD1306I2CNoBuffer::SSD1306I2CNoBuffer(uint8_t addr)
  :
    CommandDataIO(new I2CBus(0x3C)),
    SSD1306Driver(this),
    SSD1306ScreenControl(this),
    DirectWriteScreenMap(this, this, 128, 64)
  {
  }
  
  void SSD1306I2CNoBuffer::begin()
  {
    //CommandDataIO::begin();
    SSD1306Driver::begin();
    //DirectWriteScreenMap::begin();
  }
}
