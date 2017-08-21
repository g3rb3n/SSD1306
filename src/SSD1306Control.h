#ifndef _SSD1306Control_H_
#define _SSD1306Control_H_

#include "SSD1306Control_internal.h"
#include "ByteIO.h"
#include "ScreenBuffer.h"

#include <inttypes.h>

namespace g3rb3n
{

  class SSD1306Control : public BufferWriter
  {
    private:
      ByteIO* byteIO;
      uint8_t rstPin;
      bool rstEnabled;
      uint8_t pages = 8;
      uint8_t columns = 128;
      
      //Write buffer control
      uint8_t currentPage = 255;
      uint8_t currentCol = 255;

    protected:
      SSD1306Control();

    public:
      SSD1306Control(ByteIO* byteIO);
      SSD1306Control(ByteIO* byteIO, uint8_t rstPin);
      ~SSD1306Control();
      
      void begin(void);

      void display(ScreenBuffer& buffer);
      void writeBuffer(uint8_t* buffer, uint16_t size);
      void display(ScreenBuffer& buffer, uint8_t minX, uint8_t minY, uint8_t maxX, uint8_t maxY);
      void writeBuffer(uint8_t* buffer, uint16_t size, uint8_t minX, uint8_t minY, uint8_t maxX, uint8_t maxY);
      
      uint8_t writeBufferByte(uint16_t pos, uint8_t byte);
      
      // RAW LCD functions
      void command(uint8_t c);
      void data(uint8_t c);
      void setColumnAddress(uint8_t add);
      void setPageAddress(uint8_t add);
      
      void invert(boolean inv);
      void contrast(uint8_t contrast);

      // LCD Rotate Scroll functions  
      void scrollRight(uint8_t start, uint8_t stop);
      void scrollLeft(uint8_t start, uint8_t stop);
      void scrollVertRight(uint8_t start, uint8_t stop);
      void scrollVertLeft(uint8_t start, uint8_t stop);
      void scrollStop(void);
      void flipVertical(boolean flip);
      void flipHorizontal(boolean flip);
      
    private:
      volatile uint8_t *wrport, *wrreg, *rdport, *rdreg;
      uint8_t wrpinmask, rdpinmask;
      volatile uint8_t *ssport, *dcport, *ssreg, *dcreg;  // use volatile because these are fixed location port address
      uint8_t mosipinmask, sckpinmask, sspinmask, dcpinmask;
  };

}
#endif
