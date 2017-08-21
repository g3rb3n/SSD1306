#ifndef _BufferWriter_H_
#define _BufferWriter_H_

#include <inttypes.h>

class BufferWriter;

/** 
 * The BufferWriter class.
 */

class BufferWriter 
{
  public:
    virtual uint8_t writeBufferByte(uint16_t pos, uint8_t byte) = 0;
};

#endif

