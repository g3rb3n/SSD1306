#ifndef _CommandDataIO_H_
#define _CommandDataIO_H_

#include "IOBus.h"

namespace g3rb3n
{

  class CommandDataIO
  {
    private:
      IOBus* iobus;
      
    public:
      CommandDataIO();
      CommandDataIO(IOBus* iobus);
      ~CommandDataIO();

      void command(uint8_t c) const;
      void command(uint8_t* c, uint16_t len) const;
      void data(uint8_t c) const;
      void data(uint8_t* c, uint16_t len) const;
  };

}

#endif
