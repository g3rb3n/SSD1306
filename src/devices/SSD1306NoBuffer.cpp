#include "SSD1306NoBuffer.h"

namespace g3rb3n
{
  SSD1306NoBuffer::SSD1306NoBuffer(IOBus* _io)
  :
    CommandDataIO(_io),
    SSD1306Driver(this),
    SSD1306ScreenControl(this),
    DirectWriteScreenMap(this, this)
  {
  }
  
  void SSD1306NoBuffer::begin()
  {
    //CommandDataIO::begin();
    SSD1306Driver::begin();
    //DirectWriteScreenMap::begin();
  }

  void SSD1306NoBuffer::setLayout(uint8_t p, uint8_t c, uint8_t pc, uint8_t cc)
  {
    SSD1306Driver::setLayout(p, c, pc, cc);
    SSD1306ScreenControl::setLayout(p, c, pc, cc);
  }
}
