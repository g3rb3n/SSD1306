#ifndef _DirectWriteScreenMap_H_
#define _DirectWriteScreenMap_H_

#include "ScreenMap.h"
#include "ScreenControl.h"
#include "BitMap.h"
#include "../io/CommandDataIO.h"

#include "../util/types.h"

/** 
 * The ByteIO class provides a generic way for SPI / I2C / Parallel.
 */
namespace g3rb3n
{
  
  class DirectWriteScreenMap// : ScreenMap
  {
    private:
      ScreenControl* ctrl;
      CommandDataIO* io;

    public:
      DirectWriteScreenMap(ScreenControl* ctrl, CommandDataIO* io);

      uint8_t setBitMap(uint8_t* data, uint16_t page, uint16_t col, uint16_t pages, uint16_t columns);
      uint8_t setBitMap(BitMap& bitmap, uint16_t page, uint16_t col);
      
  };

}
#endif

