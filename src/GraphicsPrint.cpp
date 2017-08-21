
#include <Arduino.h>

#include "GraphicsPrint.h"
#include "ScreenBuffer.h"

#if defined(__AVR__) || defined(__arm__)
	#include <avr/pgmspace.h>
#else
	#include <pgmspace.h>
#endif

#ifndef _BV
#define _BV(x) (1<<x)
#endif

// The 31x48 font is handy, but uses a big chunk of flash memory - about 7k.
// If you want to use font 4 in your sketch, uncomment out the line below:
//#define INCLUDE_LARGE_LETTER_FONT

// This fixed ugly GCC warning "only initialized variables can be placed into program memory area"
#if defined(__AVR__)
#undef PROGMEM
#define PROGMEM __attribute__((section(".progmem.data")))
#endif

// The 31x48 font is handy, but uses a big chunk of flash memory - about 7k.
// If you want to use font 4 in your sketch, uncomment out the line below:
//#define INCLUDE_LARGE_LETTER_FONT

// Add header of the fonts here.  Remove as many as possible to conserve FLASH memory.
#include "util/font5x7.h"
#include "util/font8x16.h"
#include "util/fontlargenumber.h"
#include "util/7segment.h"
#include "util/fontlargeletter31x48.h"

// Change the total fonts included
#ifdef INCLUDE_LARGE_LETTER_FONT
#define TOTALFONTS    5
#else
#define TOTALFONTS    4
#endif

#define pages 8

namespace g3rb3n
{
  
// Add the font name as declared in the header file.  Remove as many as possible to conserve FLASH memory.
const unsigned char *GraphicsPrint::fontsPointer[]={
  font5x7
  ,font8x16
  ,sevensegment
  ,fontlargenumber
#ifdef INCLUDE_LARGE_LETTER_FONT
  ,fontlargeletter31x48
#endif
};

/** 
 * GraphicsPrint Constructor
 * reset pin and transport
 */
GraphicsPrint::GraphicsPrint(ScreenBuffer* _screen)
  : Graphics2D(_screen)
{
}

GraphicsPrint::~GraphicsPrint()
{
}

void GraphicsPrint::begin()
{
  // default 5x7 font
  setCursor(0,0);
  setFontType(0);
  Graphics2D::begin();
}

/** \brief Override Arduino's Print.

    Arduino's print overridden so that we can use uView.print().
*/
size_t GraphicsPrint::write(uint8_t c) {
  if (c == '\n')
  {
    cursorY += fontHeight;
    cursorX  = 0;
  }
  else if (c == '\r')
  {
    // skip
  }
  else
  {
    drawChar(cursorX, cursorY, c, foreColor, drawMode);
    cursorX += fontWidth + 1;
    if ((cursorX > (getLCDWidth() - fontWidth)))
    {
      cursorY += fontHeight;
      cursorX = 0;
    }
  }

  return 1;
}

/** \brief Set cursor position.

GraphicsPrint's cursor position to x,y.
*/
void GraphicsPrint::setCursor(uint8_t r, uint8_t c) 
{
  cursorX = c * (fontWidth + 1);
  cursorY = r * fontHeight;
}

/** \brief Get font width.

    The cucrrent font's width return as byte.
*/
uint8_t GraphicsPrint::getFontWidth(void) 
{
  return fontWidth;
}

/** \brief Get font height.

    The current font's height return as byte.
*/
uint8_t GraphicsPrint::getFontHeight(void) 
{
  return fontHeight;
}

/** \brief Get font starting character.

    Return the starting ASCII character of the currnet font, not all fonts start with ASCII character 0. Custom fonts can start from any ASCII character.
*/
uint8_t GraphicsPrint::getFontStartChar(void) 
{
  return fontStartChar;
}

/** \brief Get font total characters.

    Return the total characters of the current font.
*/
uint8_t GraphicsPrint::getFontTotalChar(void)
{
  return fontTotalChar;
}

/** \brief Get total fonts.

    Return the total number of fonts loaded into the GraphicsPrint's flash memory.
*/
uint8_t GraphicsPrint::getTotalFonts(void)
{
  return TOTALFONTS;
}

/** \brief Get font type.

    Return the font type number of the current font.
*/
uint8_t GraphicsPrint::getFontType(void)
{
  return fontType;
}

/** \brief Set font type.

    Set the current font type number, ie changing to different fonts base on the type provided.
*/
uint8_t GraphicsPrint::setFontType(uint8_t type)
{
  if (type >= TOTALFONTS) return false;

  fontType = type;
  fontWidth = pgm_read_byte(fontsPointer[fontType]+0);
  fontHeight = pgm_read_byte(fontsPointer[fontType]+1);
  fontStartChar = pgm_read_byte(fontsPointer[fontType]+2);
  fontTotalChar = pgm_read_byte(fontsPointer[fontType]+3);
  fontMapWidth = (pgm_read_byte(fontsPointer[fontType]+4)*100)
    + pgm_read_byte(fontsPointer[fontType]+5); // two bytes values into integer 16
  return true;
}

void GraphicsPrint::setOffset(uint8_t x, uint8_t y)
{
  cursorX = x;
  cursorY = y;
}

/** \brief Draw character.

    Draw character c using current color and current draw mode at x,y.
*/
void  GraphicsPrint::drawChar(uint8_t x, uint8_t y, uint8_t c)
{
  drawChar(x,y,c,foreColor,drawMode);
}

/** \brief Draw character with color and mode.

    Draw character c using color and draw mode at x,y.
*/
void  GraphicsPrint::drawChar(uint8_t x, uint8_t y, uint8_t c, uint8_t color, uint8_t mode)
{
  // TODO - New routine to take font of any height, at the moment limited to font height in multiple of 8 pixels  
  uint8_t rowsToDraw, row, tempC;
  uint8_t i, j, temp;
  uint16_t charPerBitmapRow, charColPositionOnBitmap, charRowPositionOnBitmap, charBitmapStartPosition;

  // no bitmap for the required c
  if ((c < fontStartChar) || (c > (fontStartChar+fontTotalChar-1)))
  {
    Serial.println("No bitmap for char");
    return;
  }
  tempC = c - fontStartChar;

  // each row (in datasheet is call page) is 8 bits high, 16 bit high character will have 2 rows to be drawn
  rowsToDraw = fontHeight / 8;  // 8 is LCD's page size, see GraphicsPrint datasheet
  if (rowsToDraw <= 1) rowsToDraw = 1;

  // the following draw function can draw anywhere on the screen, but SLOW pixel by pixel draw
  if (rowsToDraw == 1) 
  {
    for  (i=0;i<fontWidth+1;i++) 
    {
      if (i==fontWidth) // this is done in a weird way because for 5x7 font, there is no margin, this code add a margin after col 5
        temp = 0;
      else
        temp = pgm_read_byte(fontsPointer[fontType]+FONTHEADERSIZE+(tempC*fontWidth)+i);

      for (j=0;j<8;j++) 
      {      // 8 is the LCD's page height (see datasheet for explanation)
        if (temp & 0x1) 
        {
          pixel(x+i, y+j, color,mode);
        }
        else 
        {
          pixel(x+i, y+j, !color,mode);
        }

        temp >>= 1;
      }
    }
    return;
  }

  // font height over 8 bit
  // take character "0" ASCII 48 as example
  charPerBitmapRow=fontMapWidth/fontWidth;  // 256/8 =32 char per row
  charColPositionOnBitmap=tempC % charPerBitmapRow;  // =16
  charRowPositionOnBitmap=int(tempC/charPerBitmapRow); // =1
  charBitmapStartPosition=(charRowPositionOnBitmap * fontMapWidth * (fontHeight/8)) + (charColPositionOnBitmap * fontWidth) ;

  // each row on LCD is 8 bit height (see datasheet for explanation)
  for(row = 0 ; row < rowsToDraw ; ++row) 
  {
    for (i = 0 ; i < fontWidth ; ++i) 
    {
      temp=pgm_read_byte(fontsPointer[fontType]+FONTHEADERSIZE+(charBitmapStartPosition+i+(row*fontMapWidth)));
      for (j = 0 ; j < 8 ; ++j) 
      {      // 8 is the LCD's page height (see datasheet for explanation)
        if (temp & 0x1) 
        {
          pixel(x+i, y+j, color,mode);
        }
        else 
        {
          pixel(x+i, y+j, !color,mode);
        }
        temp >>=1;
      }
    }
  }
}

}
