
#include "SSD1306.h"
#include "I2CIO.h"
#include "ScreenBuffer.h"
#include "PartialUpdateScreenBuffer.h"

namespace g3rb3n
{

  /** 
   * SSD1306 Constructor
   */
  SSD1306::SSD1306()
  :
  //GraphicsPrint(new PartialUpdateScreenBuffer(128, 64, 1)),
  GraphicsPrint(new ScreenBuffer(128, 64, 1)),
  SSD1306Control(new I2CIO(0x3C))
  {
  }

  SSD1306::SSD1306(ScreenBuffer* buffer, ByteIO* io)
  :
  GraphicsPrint(buffer),
  SSD1306Control(io)
  {
  }

  SSD1306::~SSD1306()
  {
  }

  void SSD1306::begin()
  {
    SSD1306Control::begin();
    GraphicsPrint::begin();
  }
  
  void SSD1306::display()
  {
    Serial.println("SSD1306::display");
    buffer->display(*this);
//    SSD1306Control::display(*buffer);
  }
}
