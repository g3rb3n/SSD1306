#ifndef _Fixed_H_
#define _Fixed_H_

#include "../util/types.h"

/** 
 * The Fixed class provides a generic interface fixed width fonts.
 */
namespace g3rb3n
{

  class Fixed 
  {
    public:
      virtual uint8_t width() const = 0;
      virtual uint8_t height() const = 0;
      virtual uint8_t size() const = 0;

      virtual void get(uint8_t* bm, char c) const = 0;
      virtual bool has(char c) const = 0;
      
  };

}

#endif
