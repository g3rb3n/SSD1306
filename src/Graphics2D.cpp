
#include <Arduino.h>

#include "Graphics2D.h"
#include "ScreenBuffer.h"

#define pages 8

namespace g3rb3n
{


  Graphics2D::Graphics2D()
  {
  }

  /** 
   * Graphics2D Constructor
   */
  Graphics2D::Graphics2D(ScreenBuffer* _buffer) :
    buffer(_buffer)
  {
  }

  Graphics2D::~Graphics2D()
  {
  }

  void Graphics2D::begin()
  {
    setColor(WHITE);
    setDrawMode(NORM);
    clear();
  }

  /** \brief Clear screen buffer or Graphics2D's memory.

      To clear GDRAM inside the LCD controller, pass in the variable mode = ALL and to clear screen page buffer pass in the variable mode = PAGE.
  */
  void Graphics2D::clear()
  {
    clear(0);
  }

  /** \brief Clear or replace screen buffer or Graphics2D's memory with a character.

    To clear GDRAM inside the LCD controller, 
    pass in the variable mode = ALL with c character 
    and to clear screen page buffer, pass in the variable mode = PAGE with c character.
  */
  void Graphics2D::clear(uint8_t c) {
    buffer->reset(c);
    //buffer->write(ssd);
  }

  /** \brief Transfer display memory.

      Bulk move the screen buffer to the Graphics2D controller's memory so that images/graphics drawn on the screen buffer will be displayed on the OLED.
  */
  void Graphics2D::display(void) 
  {
    //buffer->write(ssd);
  }

  /** \brief Draw pixel.

  Draw pixel using the current fore color and current draw mode in the screen buffer's x,y position.
  */
  void Graphics2D::pixel(uint8_t x, uint8_t y)
  {
    pixel(x, y, foreColor, drawMode);
  }

  /** \brief Draw pixel.

  Draw pixel using the current fore color and current draw mode in the screen buffer's x,y position.
  */
  void Graphics2D::pixel(uint8_t x, uint8_t y, uint8_t color)
  {
    pixel(x, y, color, drawMode);
  }

  /** \brief Draw pixel with color and mode.

  Draw color pixel in the screen buffer's x,y position with NORM or XOR draw mode.
  */
  void Graphics2D::pixel(uint8_t x, uint8_t y, uint8_t color, uint8_t mode)
  {
    buffer->set(x, y, color);
  }

  /** \brief Draw line.

  Draw line using current fore color and current draw mode from x0,y0 to x1,y1 of the screen buffer.
  */
  void Graphics2D::line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
    line(x0,y0,x1,y1,foreColor,drawMode);
  }

  /** \brief Draw line with color and mode.

  Draw line using color and mode from x0,y0 to x1,y1 of the screen buffer.
  */
  void Graphics2D::line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color, uint8_t mode) {
    uint8_t steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
      swap(x0, y0);
      swap(x1, y1);
    }

    if (x0 > x1) {
      swap(x0, x1);
      swap(y0, y1);
    }

    uint8_t dx, dy;
    dx = x1 - x0;
    dy = abs(y1 - y0);

    int8_t err = dx / 2;
    int8_t ystep;

    if (y0 < y1) {
      ystep = 1;
    } else {
      ystep = -1;}

    for (; x0<x1; x0++) {
      if (steep) {
        pixel(y0, x0, color, mode);
      } else {
        pixel(x0, y0, color, mode);
      }
      err -= dy;
      if (err < 0) {
        y0 += ystep;
        err += dx;
      }
    }
  }

  /** \brief Draw horizontal line.

  Draw horizontal line using current fore color and current draw mode from x,y to x+width,y of the screen buffer.
  */
  void Graphics2D::lineH(uint8_t x, uint8_t y, uint8_t width) {
    line(x,y,x+width,y,foreColor,drawMode);
  }

  /** \brief Draw horizontal line with color and mode.

  Draw horizontal line using color and mode from x,y to x+width,y of the screen buffer.
  */
  void Graphics2D::lineH(uint8_t x, uint8_t y, uint8_t width, uint8_t color, uint8_t mode) {
    line(x,y,x+width,y,color,mode);
  }

  /** \brief Draw vertical line.

  Draw vertical line using current fore color and current draw mode from x,y to x,y+height of the screen buffer.
  */
  void Graphics2D::lineV(uint8_t x, uint8_t y, uint8_t height) {
    line(x,y,x,y+height,foreColor,drawMode);
  }

  /** \brief Draw vertical line with color and mode.

  Draw vertical line using color and mode from x,y to x,y+height of the screen buffer.
  */
  void Graphics2D::lineV(uint8_t x, uint8_t y, uint8_t height, uint8_t color, uint8_t mode) {
    line(x,y,x,y+height,color,mode);
  }

  /** \brief Draw rectangle.

  Draw rectangle using current fore color and current draw mode from x,y to x+width,y+height of the screen buffer.
  */
  void Graphics2D::rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
    rect(x,y,width,height,foreColor,drawMode);
  }

  /** \brief Draw rectangle with color and mode.

  Draw rectangle using color and mode from x,y to x+width,y+height of the screen buffer.
  */
  void Graphics2D::rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color , uint8_t mode) {
    uint8_t tempHeight;

    lineH(x,y, width, color, mode);
    lineH(x,y+height-1, width, color, mode);

    tempHeight=height-2;

    // skip drawing vertical lines to avoid overlapping of pixel that will
    // affect XOR plot if no pixel in between horizontal lines
    if (tempHeight<1) return;

    lineV(x,y+1, tempHeight, color, mode);
    lineV(x+width-1, y+1, tempHeight, color, mode);
  }

  /** \brief Draw filled rectangle.

  Draw filled rectangle using current fore color and current draw mode from x,y to x+width,y+height of the screen buffer.
  */
  void Graphics2D::rectFill(uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
    rectFill(x,y,width,height,foreColor,drawMode);
  }

  /** \brief Draw filled rectangle with color and mode.

  Draw filled rectangle using color and mode from x,y to x+width,y+height of the screen buffer.
  */
  void Graphics2D::rectFill(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color , uint8_t mode) {
    // TODO - need to optimise the memory map draw so that this function will not call pixel one by one
    for (int i=x; i<x+width;i++) {
      lineV(i,y, height, color, mode);
    }
  }

  /** \brief Draw circle.

      Draw circle with radius using current fore color and current draw mode at x,y of the screen buffer.
  */
  void Graphics2D::circle(uint8_t x0, uint8_t y0, uint8_t radius) {
    circle(x0,y0,radius,foreColor,drawMode);
  }

  /** \brief Draw circle with color and mode.

  Draw circle with radius using color and mode at x,y of the screen buffer.
  */
  void Graphics2D::circle(uint8_t x0, uint8_t y0, uint8_t radius, uint8_t color, uint8_t mode) {
    //TODO - find a way to check for no overlapping of pixels so that XOR draw mode will work perfectly
    int8_t f = 1 - radius;
    int8_t ddF_x = 1;
    int8_t ddF_y = -2 * radius;
    int8_t x = 0;
    int8_t y = radius;

    pixel(x0, y0+radius, color, mode);
    pixel(x0, y0-radius, color, mode);
    pixel(x0+radius, y0, color, mode);
    pixel(x0-radius, y0, color, mode);

    while (x<y) {
      if (f >= 0) {
        y--;
        ddF_y += 2;
        f += ddF_y;
      }
      x++;
      ddF_x += 2;
      f += ddF_x;

      pixel(x0 + x, y0 + y, color, mode);
      pixel(x0 - x, y0 + y, color, mode);
      pixel(x0 + x, y0 - y, color, mode);
      pixel(x0 - x, y0 - y, color, mode);

      pixel(x0 + y, y0 + x, color, mode);
      pixel(x0 - y, y0 + x, color, mode);
      pixel(x0 + y, y0 - x, color, mode);
      pixel(x0 - y, y0 - x, color, mode);

    }
  }

  /** \brief Draw filled circle.

      Draw filled circle with radius using current fore color and current draw mode at x,y of the screen buffer.
  */
  void Graphics2D::circleFill(uint8_t x0, uint8_t y0, uint8_t radius) {
    circleFill(x0,y0,radius,foreColor,drawMode);
  }

  /** \brief Draw filled circle with color and mode.

      Draw filled circle with radius using color and mode at x,y of the screen buffer.
  */
  void Graphics2D::circleFill(uint8_t x0, uint8_t y0, uint8_t radius, uint8_t color, uint8_t mode) {
    // TODO - - find a way to check for no overlapping of pixels so that XOR draw mode will work perfectly
    int8_t f = 1 - radius;
    int8_t ddF_x = 1;
    int8_t ddF_y = -2 * radius;
    int8_t x = 0;
    int8_t y = radius;

    // Temporary disable fill circle for XOR mode.
    if (mode==XOR) return;

    for (uint8_t i=y0-radius; i<=y0+radius; i++) {
      pixel(x0, i, color, mode);
    }

    while (x<y) {
      if (f >= 0) {
        y--;
        ddF_y += 2;
        f += ddF_y;
      }
      x++;
      ddF_x += 2;
      f += ddF_x;

      for (uint8_t i=y0-y; i<=y0+y; i++) {
        pixel(x0+x, i, color, mode);
        pixel(x0-x, i, color, mode);
      }
      for (uint8_t i=y0-x; i<=y0+x; i++) {
        pixel(x0+y, i, color, mode);
        pixel(x0-y, i, color, mode);
      }
    }
  }

  /** \brief Get LCD height.

      The height of the LCD return as byte.
  */
  uint8_t Graphics2D::getLCDHeight(void)
  {
    return buffer->height;
  }

  /** \brief Get LCD width.

      The width of the LCD return as byte.
  */
  uint8_t Graphics2D::getLCDWidth(void)
  {
    return buffer->width;
  }

  /** \brief Set color.

      Set the current draw's color. Only WHITE and BLACK available.
  */
  void Graphics2D::setColor(uint8_t color)
  {
    foreColor = color;
  }

  /** \brief Set draw mode.

      Set current draw mode with NORM or XOR.
  */
  void Graphics2D::setDrawMode(uint8_t mode)
  {
    drawMode = mode;
  }

}
