#ifndef _BufferWriter_H_
#define _BufferWriter_H_

#include "../util/types.h"

/** 
 * The BufferWriter class.
 */

class BufferWriter 
{
  public:
    virtual uint8_t writeBufferByte(uint16_t pos, uint8_t byte) = 0;
    virtual uint8_t writeBufferBytes(uint16_t pos, uint8_t* byte, uint16_t len) = 0;
};

#endif

