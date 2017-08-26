#ifndef _ScreenMap_H_
#define _ScreenMap_H_

#include "../util/types.h"

namespace g3rb3n
{
  
  class ScreenMap
  {
    public:
      enum class Error
      {
        Ok = 0,
        HorizontalOverflow,
        VerticalOverflow
      };

      virtual uint8_t setBitMap(uint16_t page, uint16_t col, uint8_t* pixels, uint16_t pages, uint16_t columns);
      virtual uint16_t width() const;
      virtual uint16_t height() const;
  };

}
#endif

