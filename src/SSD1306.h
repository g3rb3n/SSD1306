#ifndef _SSD1306_H_
#define _SSD1306_H_

#include "SSD1306Control.h"
#include "ByteIO.h"
#include "ScreenBuffer.h"
#include "GraphicsPrint.h"
#include "Graphics2D.h"

#include <inttypes.h>

namespace g3rb3n
{

  class SSD1306 : public SSD1306Control , public GraphicsPrint
  {
    private:

    public:
      SSD1306();
      SSD1306(ScreenBuffer* buffer, ByteIO* io);
      ~SSD1306();

      void begin();

      void display();
  };

}
#endif
