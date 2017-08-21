#ifndef _Graphics2D_H_
#define _Graphics2D_H_

#define BLACK 0
#define WHITE 1

#define NORM				0
#define XOR					1

#define swap(a, b) { uint8_t t = a; a = b; b = t; }

#include "ScreenBuffer.h"

#include <inttypes.h>

namespace g3rb3n
{

  class Graphics2D
  {
    protected:
      ScreenBuffer* buffer;
    	uint8_t foreColor,drawMode;

    protected:
      Graphics2D();

    public:
      Graphics2D(ScreenBuffer* buffer);
      ~Graphics2D();

      void begin(void);

    	void clear();
    	void clear(uint8_t c);
    	void display();
      
    	void pixel(uint8_t x, uint8_t y);
      void pixel(uint8_t x, uint8_t y, uint8_t color);
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

    	void drawBitmap(uint8_t * bitArray);

    	uint8_t getLCDWidth(void);
    	uint8_t getLCDHeight(void);
    	void setColor(uint8_t color);
    	void setDrawMode(uint8_t mode);
    };

}
#endif
