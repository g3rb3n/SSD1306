#include "GraphicsPrint.h"

namespace g3rb3n
{
  
  /** 
   * GraphicsPrint Constructor
   * reset pin and transport
   */
  GraphicsPrint::GraphicsPrint(ScreenBuffer* _screen, Fixed* _font)
  :
  Graphics2D(_screen),
  font(_font)
  {
  }

  GraphicsPrint::~GraphicsPrint()
  {
  }

  void GraphicsPrint::begin()
  {
    setCursor(0,0);
    Graphics2D::begin();
  }

  /**
  * Arduino's print overridden.
  */
  size_t GraphicsPrint::write(uint8_t c)
  {
    if (c == '\n')
    {
      y += font->height();
      x  = 0;
    }
    else if (c == '\r')
    {
    }
    else
    {
      drawChar(x, y, c);
      x += font->width() + 1;
      if (x > width() - font->width())
      {
        y += font->height();
        x = 0;
      }
    }

    return 1;
  }

  void GraphicsPrint::setCursor(uint8_t r, uint8_t c) 
  {
    x = c * (font->width() + 1);
    y = r * font->height();
  }

  void GraphicsPrint::setOffset(uint8_t _x, uint8_t _y)
  {
    x = _x;
    y = _y;
  }

  void GraphicsPrint::setChar(uint8_t page, uint8_t col, uint8_t c)
  {
    if (!font->has(c)) return;
    uint8_t bm[font->height()/8];
    for (uint8_t i = 0 ; i < font->height()/8 ; ++i)
      bm[i] = 0x00;
    uint8_t bytes[font->size()];
    font->get(bytes, c);
    setBitmap(bytes, page, col, font->height() / 8, font->width());
    setBitmap(bm, page, col + font->width(), font->height() / 8, 1);
  }

  void GraphicsPrint::drawCharByPixels(uint8_t x, uint8_t y, uint8_t c)
  {
    if (!font->has(c)) return;

    uint8_t bytes[font->height() / 8 * font->width()];
    font->get(bytes, c);
    drawBitmap(bytes, x, y, font->width(), font->height());
  }

  void  GraphicsPrint::drawChar(uint8_t x, uint8_t y, uint8_t c)
  {
    if (y % 8 == 0 && font->height() % 8 == 0)
    {
      setChar(y / 8, x, c);
      return;
    }
    drawCharByPixels(x, y, c);
  }
}
