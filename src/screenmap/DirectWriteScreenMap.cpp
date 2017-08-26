#include "DirectWriteScreenMap.h"

namespace g3rb3n
{
  DirectWriteScreenMap::DirectWriteScreenMap(ScreenControl* _ctrl, CommandDataIO* _io, uint16_t width, uint16_t height)
  :
  ctrl(_ctrl),
  io(_io),
  _width(width),
  _height(height)
  {
  }
/*
  uint8_t DirectWriteScreenMap::set(uint8_t byte, uint16_t pos)
  {
    uint8_t page = pos / 128;
    uint8_t col = pos % 128;
    ctrl->setPageColumnMode(page, col, 1, 1);
    io->data(byte);
  }
*/
  uint8_t DirectWriteScreenMap::setBitMap(uint16_t page, uint16_t column, uint8_t* data, uint16_t pages, uint16_t columns)
  {
    ctrl->setPageColumnMode(page, column, pages, columns);
    io->data(data, pages * columns);
    return 0;
  }

  uint8_t DirectWriteScreenMap::setBitMap(uint16_t page, uint16_t column, BitMap& bitmap)
  {
    return setBitMap(page, column, bitmap.getBuffer(), bitmap.height, bitmap.width);
  }

}
