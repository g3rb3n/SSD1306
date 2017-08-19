
#ifndef _BYTE_IO_H_
#define _BYTE_IO_H_

#include <inttypes.h>

class ByteIO;

/** 
 * The ByteIO class provides a generic way for SPI / I2C / Parallel.
 */

class ByteIO 
{
  public:
    virtual uint8_t write(uint8_t mode, uint8_t b) const = 0;
    virtual uint8_t read(uint8_t mode, uint8_t& b) const = 0;
};

#endif

