#include "SSD1306I2CNoBuffer64x48.h"

namespace g3rb3n
{
  SSD1306I2CNoBuffer64x48::SSD1306I2CNoBuffer64x48(uint8_t addr)
  :
    CommandDataIO(new I2CBus(0x3C)),
    SSD1306Driver(this),
    SSD1306ScreenControl(this, 6, 64, 2, 32),
    DirectWriteScreenMap(this, this)
  {
  }
  
  void SSD1306I2CNoBuffer64x48::begin()
  {
    SSD1306Driver::begin();
  }
}
