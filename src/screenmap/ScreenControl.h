#ifndef _ScreenControl_H_
#define _ScreenControl_H_

#include <inttypes.h>

namespace g3rb3n
{

  class ScreenControl;

  class ScreenControl
  {
    public:
      virtual void setPageColumnMode(uint16_t startPage, uint16_t startColumn, uint16_t pages, uint16_t columns) = 0;
  };

}
#endif

