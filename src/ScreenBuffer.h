#ifndef _ScreenBuffer_H_
#define _ScreenBuffer_H_

#include <Arduino.h>

#include "ByteIO.h"
#include "BufferWriter.h"
#include <inttypes.h>

#if defined(__AVR__) || defined(__arm__)
  #include <avr/pgmspace.h>
#else
  #include <pgmspace.h>
#endif

// This fixed ugly GCC warning "only initialized variables can be placed into program memory area"
#if defined(__AVR__)
#undef PROGMEM
#define PROGMEM __attribute__((section(".progmem.data")))
#endif

#define Pixel uint8_t

namespace g3rb3n
{

  class ScreenBuffer
  {
    public:
      const uint8_t width;
      const uint8_t height;
      const uint16_t size;

    protected:
      uint8_t pages = 8;
      uint8_t columns = 128;
      uint8_t depth;
      uint8_t* buffer;

    public:
      ScreenBuffer(uint8_t width, uint8_t height, uint8_t depth);
      ~ScreenBuffer();

      void begin();
      
      virtual void set(uint8_t x, uint8_t y, Pixel pixel);
      void get(uint8_t x, uint8_t y, Pixel& pixel);
      bool offScreen(uint8_t x, uint8_t y);

      virtual void reset(Pixel data);
      virtual void reset();

      virtual void display(BufferWriter& bw);

      uint8_t* screenBuffer();
//      void write(SSD1306* ssd);
  };

}

#endif
