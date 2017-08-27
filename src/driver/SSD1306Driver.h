#ifndef _SSD1306Driver_H_
#define _SSD1306Driver_H_

#include "SSD1306DriverEnums.h"
#include "../io/CommandDataIO.h"
#include "../screenbuffer/BufferWriter.h"

namespace g3rb3n
{

  class SSD1306Driver : public BufferWriter
  {
    private:
      CommandDataIO* io;
      uint8_t rstPin;
      bool rstEnabled;
      AddressingMode addressing = AddressingMode::Horizontal;
      bool isFlippedHorizontal = false;

      uint8_t columns = 128;
      uint8_t pages = 8;
      uint8_t columnOffset = 0;
      uint8_t pageOffset = 0;

      //Write buffer control
      uint8_t currentPage = 255;
      uint8_t currentCol = 255;

    protected:
      SSD1306Driver();

    public:
      SSD1306Driver(CommandDataIO* byteIO);
      SSD1306Driver(CommandDataIO* byteIO, uint8_t rstPin);
      ~SSD1306Driver();
      
      void begin(void);

      void setLayout(uint8_t _colOffset, uint8_t pageOffset, uint8_t columns, uint8_t pages);
      uint8_t writeBufferByte(uint16_t pos, uint8_t byte);
      uint8_t writeBufferBytes(uint16_t pos, uint8_t* byte, uint16_t len);

      // Orientation
      void flipVertical(bool flip);
      void flipHorizontal(bool flip);


      AddressingMode addressingMode() const;
      
      // Fundamental commands for inverting and contrast.
      void setContrast(uint8_t contrast);
      void setEntireDisplayOn(bool on);
      void setInverse(bool inv);
      void setDisplayOn(bool on);

      // Scroll functions
      void setHorizontalScroll(HorizontalDirection dir, TimeInterval interval, uint8_t startPage, uint8_t endPage);
      void setVerticalHorizontalScroll(VerticalHorizontalDirection dir, TimeInterval interval, uint8_t startPage, uint8_t endPage, uint8_t verticalOffset);
      void enableScroll(bool on);
      void setVerticalScrollArea(uint8_t fixedRows, uint8_t scrollRows);
      
      void setAddressingMode(AddressingMode mode);
      void setPageAddress(uint8_t addr);
      void setColumnAddress(uint8_t addr);
      void setPageRange(uint8_t start, uint8_t end);
      void setColumnRange(uint8_t start, uint8_t end);
      
      void setDisplayStartLine(uint8_t line);
      void setDisplayOffset(uint8_t offset);
      void setSegmentRemapOn(bool on);
      void setComOutputScanDirRemapOn(bool on);
      
      void setMultiplexRatio(uint8_t ratio);
      void setComPinsHardwareConfig(bool alternative, bool com);
      
      void setChargePumpOn(bool on);
      void setDisplayClockDivide(uint8_t f, uint8_t ratio);
  };

}
#endif
