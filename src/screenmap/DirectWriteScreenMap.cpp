#include "DirectWriteScreenMap.h"

namespace g3rb3n
{
  DirectWriteScreenMap::DirectWriteScreenMap(ScreenControl* _ctrl, CommandDataIO* _io)
  :
  ctrl(_ctrl),
  io(_io)
  {
  }

  uint8_t DirectWriteScreenMap::setBitMap(uint8_t* data, uint16_t page, uint16_t column, uint16_t pages, uint16_t columns)
  {
    ctrl->setPageColumnMode(page, column, pages, columns);
    io->data(data, pages * columns);
    return 0;
  }

  uint8_t DirectWriteScreenMap::setBitMap(BitMap& bitmap, uint16_t page, uint16_t column)
  {
    return setBitMap(bitmap.getBuffer(), page, column, bitmap.height, bitmap.width);
  }

}
