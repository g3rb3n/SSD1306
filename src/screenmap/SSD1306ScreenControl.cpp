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

  SSD1306ScreenControl::~SSD1306ScreenControl()
  {}

  void SSD1306ScreenControl::setPageColumnMode(uint16_t page, uint16_t column, uint16_t pages, uint16_t columns)
  {
    uint8_t endPage = MIN(page + pages - 1, 7);
    uint8_t endColumn = MIN(column + columns - 1, 127);
    uint8_t cmd[] = {
//      SSD1306_ADDRESSING_MODE, SSD1306_ADDRESSING_MODE_HORIZONTAL,
      SSD1306_COLUMN_RANGE, column, endColumn, 
      SSD1306_PAGE_RANGE, page, endPage
    };

    io->command(cmd, 6);
  }
}