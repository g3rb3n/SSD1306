
#ifndef _GRAPHICAL_MEMORY_H_
#define _GRAPHICAL_MEMORY_H_

#include <inttypes.h>

class GraphicalMemory;

/** 
 * Way to access graphical memory
 */

class GraphicalMemory 
{
  public:
    virtual uint8_t write(uint8_t x, uint8_t y, uint8_t b) = 0;
    virtual uint8_t write(uint16_t pos, uint8_t b) = 0;
    virtual uint8_t write(uint8_t b) = 0;
    
    virtual uint8_t _xor(uint8_t x, uint8_t y) = 0;
    virtual uint8_t _or(uint8_t x, uint8_t y) = 0;
    virtual uint8_t _and(uint8_t x, uint8_t y) = 0;

    virtual uint8_t display() = 0;
};

#endif

