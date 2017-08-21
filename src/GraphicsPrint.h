#ifndef _GraphicsPrint_H_
#define _GraphicsPrint_H_

#include "Graphics2D.h"
#include "ScreenBuffer.h"
#include "ByteIO.h"

#include <inttypes.h>

#if defined(__AVR__) || defined(__arm__)
	#include <avr/pgmspace.h>
#else
	#include <pgmspace.h>
#endif

#define FONTHEADERSIZE		6

namespace g3rb3n
{

  class GraphicsPrint : public Graphics2D, public Print
  {
    private:      
    	uint8_t fontWidth, fontHeight, fontType, fontStartChar, fontTotalChar;
    	uint16_t fontMapWidth;
      uint8_t cursorX;
      uint8_t cursorY;
    	static const unsigned char *fontsPointer[];
      
    public:
      GraphicsPrint(ScreenBuffer* screen);
      ~GraphicsPrint();

      virtual size_t write(uint8_t);

      void begin(void);
      
    	void setCursor(uint8_t r, uint8_t c);
      void setOffset(uint8_t x, uint8_t y);

      void drawChar(uint8_t x, uint8_t y, uint8_t c);
      void drawChar(uint8_t x, uint8_t y, uint8_t c, uint8_t color, uint8_t mode);

    	// Font functions
    	uint8_t getFontWidth(void);
    	uint8_t getFontHeight(void);
    	uint8_t getTotalFonts(void);
    	uint8_t getFontType(void);
    	uint8_t setFontType(uint8_t type);
    	uint8_t getFontStartChar(void);
    	uint8_t getFontTotalChar(void);
    };

}
#endif
