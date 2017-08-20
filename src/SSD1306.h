#ifndef _SSD1306_H_
#define _SSD1306_H_

#include <SSD1306_internal.h>
#include <ByteIO.h>
#include <GraphicalMemory.h>
#include <inttypes.h>

namespace g3rb3n
{

  class SSD1306 : public Print
  {
    private:
      uint8_t width = 128;
      uint8_t height = 64;
      ByteIO* byteIO;
      uint8_t rstPin;
      bool rstEnabled;
      GraphicalMemory* memory;
      uint8_t pages = 8;
      uint8_t columns = 128;

    public:
      SSD1306(ByteIO* byteIO, GraphicalMemory* memory);
      SSD1306(ByteIO* byteIO, GraphicalMemory* memory, uint8_t rstPin);
      ~SSD1306();
    	
    	void begin(void);
    	virtual size_t write(uint8_t);

    	// RAW LCD functions
    	void command(uint8_t c);
    	void data(uint8_t c);
    	void setColumnAddress(uint8_t add);
    	void setPageAddress(uint8_t add);
    	
    	// LCD Draw functions
    	void clear(uint8_t mode);
    	void clear(uint8_t mode, uint8_t c);
    	void invert(boolean inv);
    	void contrast(uint8_t contrast);
    	void display(void);
    	void setCursor(uint8_t x, uint8_t y);
    	void pixel(uint8_t x, uint8_t y);
    	void pixel(uint8_t x, uint8_t y, uint8_t color, uint8_t mode);
    	void line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
    	void line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color, uint8_t mode);
    	void lineH(uint8_t x, uint8_t y, uint8_t width);
    	void lineH(uint8_t x, uint8_t y, uint8_t width, uint8_t color, uint8_t mode);
    	void lineV(uint8_t x, uint8_t y, uint8_t height);
    	void lineV(uint8_t x, uint8_t y, uint8_t height, uint8_t color, uint8_t mode);
    	void rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height);
    	void rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color , uint8_t mode);
    	void rectFill(uint8_t x, uint8_t y, uint8_t width, uint8_t height);
    	void rectFill(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color , uint8_t mode);
    	void circle(uint8_t x, uint8_t y, uint8_t radius);
    	void circle(uint8_t x, uint8_t y, uint8_t radius, uint8_t color, uint8_t mode);
    	void circleFill(uint8_t x0, uint8_t y0, uint8_t radius);
    	void circleFill(uint8_t x0, uint8_t y0, uint8_t radius, uint8_t color, uint8_t mode);
    	void drawChar(uint8_t x, uint8_t y, uint8_t c);
    	void drawChar(uint8_t x, uint8_t y, uint8_t c, uint8_t color, uint8_t mode);
    	void drawBitmap(uint8_t * bitArray);
    	uint8_t getLCDWidth(void);
    	uint8_t getLCDHeight(void);
    	void setColor(uint8_t color);
    	void setDrawMode(uint8_t mode);
    	//uint8_t *getScreenBuffer(void);

    	// Font functions
    	uint8_t getFontWidth(void);
    	uint8_t getFontHeight(void);
    	uint8_t getTotalFonts(void);
    	uint8_t getFontType(void);
    	uint8_t setFontType(uint8_t type);
    	uint8_t getFontStartChar(void);
    	uint8_t getFontTotalChar(void);

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
    	volatile uint8_t *ssport, *dcport, *ssreg, *dcreg;	// use volatile because these are fixed location port address
    	uint8_t mosipinmask, sckpinmask, sspinmask, dcpinmask;
    	uint8_t foreColor,drawMode,fontWidth, fontHeight, fontType, fontStartChar, fontTotalChar, cursorX, cursorY;
    	uint16_t fontMapWidth;
    	static const unsigned char *fontsPointer[];
  };

}
#endif
