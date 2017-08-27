#include "SSD1306ScreenControl.h"
#include "SSD1306ScreenControlCommands.h"
#include "util/MinMax.h"

namespace g3rb3n
{
  SSD1306ScreenControl::SSD1306ScreenControl()
  {}

  SSD1306ScreenControl::SSD1306ScreenControl(CommandDataIO* _io)
  :
  io(_io)
  {}

  SSD1306ScreenControl::SSD1306ScreenControl(CommandDataIO* _io, 
    uint8_t _pages, uint8_t _columns, 
    uint8_t _pageOffset, uint8_t _columnOffset)
  :
  pages(_pages),
  columns(_columns),
  pageOffset(_pageOffset),
  columnOffset(_columnOffset),
  io(_io)
  {}

  SSD1306ScreenControl::~SSD1306ScreenControl()
  {}

  void SSD1306ScreenControl::setLayout(
    uint8_t _pages, uint8_t _columns, 
    uint8_t _pageOffset, uint8_t _columnOffset)
  {
    pages = _pages;
    columns = _columns;
    pageOffset = _pageOffset;
    columnOffset = _columnOffset;
  }
  
  void SSD1306ScreenControl::setPageColumnMode(
    uint16_t page, uint16_t column, 
    uint16_t _pages, uint16_t _columns)
  {
    page += pageOffset;
    column += columnOffset;
    uint8_t endPage = MIN(page + _pages - 1, pages + pageOffset);
    uint8_t endColumn = MIN(column + _columns - 1, columns + columnOffset);
    uint8_t cmd[] = {
//      SSD1306_ADDRESSING_MODE, SSD1306_ADDRESSING_MODE_HORIZONTAL,
      SSD1306_COLUMN_RANGE, column, endColumn, 
      SSD1306_PAGE_RANGE, page, endPage
    };

    io->command(cmd, 6);
  }
}
