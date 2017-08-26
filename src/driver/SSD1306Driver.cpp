#include "SSD1306Driver.h"
#include "SSD1306DriverCommands.h"

#include <Arduino.h>

//#define DEBUG

namespace g3rb3n
{

  /** 
   * SSD1306Driver constructor
   * IO only, disable reset pin functionality
   */
  SSD1306Driver::SSD1306Driver(CommandDataIO* _io):
    io(_io),
    rstEnabled(false)
  {
  }

  /** 
   * SSD1306Driver constructor
   * IO only and reset pin
   */
  SSD1306Driver::SSD1306Driver(CommandDataIO* _io, uint8_t _rstPin):
    io(_io),
    rstPin(_rstPin),
    rstEnabled(true) 
  {
  }

  /** 
   * SSD1306Driver destructor
   */
  SSD1306Driver::~SSD1306Driver()
  {
  }

  /** 
   * Initialisation of SSD1306 OLED display.
   * Follows the schema from the documentation.
   * When reset pin is enabled it first perfoms a hard reset. 
   */
  void SSD1306Driver::begin()
  {
    if (rstEnabled)
    {
      pinMode(rstPin, OUTPUT);

      // Display reset routine
      pinMode(rstPin, OUTPUT);  // Set RST pin as OUTPUT
      digitalWrite(rstPin, HIGH);  // Initially set RST HIGH
      delay(5);  // VDD (3.3V) goes high at start, lets just chill for 5 ms
      digitalWrite(rstPin, LOW);  // Bring RST low, reset the display
      delay(10);  // wait 10ms
      digitalWrite(rstPin, HIGH);  // Set RST HIGH, bring out of reset
    }
    // Display Init sequence 
    //Set MUX Ratio A8h, 3Fh
    //command(0xA8);
    //command(0x3F);
    setMultiplexRatio(0x3F);

    //Set Display Offset D3h, 00h 
    //command(0xD3);
    //command(0x00);
    setDisplayOffset(0);
    
    //Set Display Start Line 40h
    //command(0x40);
    setDisplayStartLine(0);

    //Set Segment re-map A0h/A1h
    //command(0xA0);
    setSegmentRemapOn(false);

    //Set COM Output Scan Direction C0h/C8h
    //command(0xC0);
    setComOutputScanDirRemapOn(false);
    
    //Set Contrast Control  81h, 7Fh
    //command(0x81);
    //command(0x7F);
    setContrast(127);

    //Disable Entire Display On A4h
    //io->command(0xA4);
    setEntireDisplayOn(false);

    //Set Normal Display A6h
    //io->command(0xA6);
    setInverse(false);

    //Set Osc Frequency D5h, 80h
    //command(0xD5);
    //command(0x80);
    setDisplayClockDivide(0x08, 0x00);
    
    //Set COM Pins hardware configuration DAh, 02 
    //command(0xDA);
    ////command(0x02);
    //command(0x12);
    setComPinsHardwareConfig(false, true);
    
    //Enable charge pump regulator 8Dh, 14h
    //command(0x8D);
    //command(0x14);
    setChargePumpOn(true);
    
    //Display On AFh
    //command(0xAF);
    setDisplayOn(true);
    
    //Set page addressing mode
    //command(0x20);
    //command(0x02);
    setAddressingMode(addressing);
  }

  AddressingMode SSD1306Driver::addressingMode() const
  {
    return addressing;
  }
  
  // Fundamental commands for inverting and contrast.
  void SSD1306Driver::setContrast(uint8_t contrast)
  {
    uint8_t cmds[] = 
    {
      SSD1306_CMD_CONTRAST,
      contrast
    };
    io->command(cmds, 2);
  }
  
  void SSD1306Driver::setEntireDisplayOn(bool on)
  {
    uint8_t cmd = SSD1306_CMD_ENTIRE_DISPLAY_ON | (on ? SSD1306_VAL_ENTIRE_DISPLAY_ON : 0);
    io->command(cmd);
  }
  
  void SSD1306Driver::setInverse(bool inv)
  {
    uint8_t cmd = SSD1306_CMD_INVERSE_DISPLAY | (inv ? SSD1306_VAL_INVERSE_DISPLAY : 0);
    io->command(cmd);
  }

  void SSD1306Driver::setDisplayOn(bool on)
  {
    uint8_t cmd = SSD1306_CMD_DISPLAY_ON | (on ? SSD1306_VAL_DISPLAY_ON : 0);
    io->command(cmd);
  }

  // Scroll functions
  void SSD1306Driver::setHorizontalScroll(
    HorizontalDirection dir, 
    TimeInterval interval, 
    uint8_t startPage, 
    uint8_t endPage)
  {
    uint8_t d = static_cast<uint8_t>(dir);
    uint8_t cmds[] = 
    {
      SSD1306_CMD_SCROLL_H_DIR | d,
      SSD1306_CMD_DUMMY_00,
      SSD1306_VAL_PAGE_ADDRESS & startPage,
      static_cast<uint8_t>(interval),
      SSD1306_VAL_PAGE_ADDRESS & endPage,
      SSD1306_CMD_DUMMY_00,
      SSD1306_CMD_DUMMY_FF
    };
    io->command(cmds, 7);
  }

  void SSD1306Driver::setVerticalHorizontalScroll(
    VerticalHorizontalDirection dir, 
    TimeInterval interval, 
    uint8_t startPage, 
    uint8_t endPage, 
    uint8_t verticalOffset)
  {
    uint8_t cmds[] = 
    {
      SSD1306_CMD_SCROLL_HV_DIR | static_cast<uint8_t>(dir),
      SSD1306_CMD_DUMMY_00,
      SSD1306_VAL_PAGE_ADDRESS & startPage,
      static_cast<uint8_t>(interval),
      SSD1306_VAL_PAGE_ADDRESS & endPage,
      SSD1306_VAL_SCROLL_V_OFF
    };
    io->command(cmds, 6);
  }

  void SSD1306Driver::enableScroll(bool on)
  {
    uint8_t cmd = SSD1306_CMD_SCROLL_ON | (on ? SSD1306_VAL_SCROLL_ON : 0);
    io->command(cmd);
  }
  
  void SSD1306Driver::setVerticalScrollArea(uint8_t fixedRows, uint8_t scrollRows)
  {
    uint8_t cmds[] = 
    {
      SSD1306_CMD_SCROLL_V_AREA,
      SSD1306_VAL_SCROLL_V_AREA & fixedRows,
      SSD1306_VAL_SCROLL_V_AREA & scrollRows,
    };
    io->command(cmds, 3);
  }

  void SSD1306Driver::setAddressingMode(AddressingMode mode)
  {
    uint8_t cmd[] = {
      SSD1306_CMD_MEMORY_ADDRESSING_MODE,
      static_cast<uint8_t>(mode)
    };
    io->command(cmd, 2);
  }

  void SSD1306Driver::setPageAddress(uint8_t addr)
  {
    uint8_t cmd = SSD1306_CMD_PAGE_ADDRESS | (SSD1306_VAL_PAGE_ADDRESS & addr);
    io->command(cmd);
  }

  void SSD1306Driver::setColumnAddress(uint8_t addr)
  {
    uint8_t low = addr & 0x0F;
    uint8_t high = addr >> 4;
    uint8_t cmds[] = 
    {
      SSD1306_CMD_COLUMN_ADDRESS_HIGH | low,
      SSD1306_CMD_COLUMN_ADDRESS_LOW | high
    };
    io->command(cmds, 2);
  }

  void SSD1306Driver::setPageRange(uint8_t start, uint8_t end)
  {
    uint8_t cmds[] = 
    {
      SSD1306_CMD_PAGE_ADDRESS_RANGE,
      start,
      end
    };
    io->command(cmds, 3);
  }
  
  void SSD1306Driver::setColumnRange(uint8_t start, uint8_t end)
  {
    uint8_t cmds[] = 
    {
      SSD1306_CMD_COLUMN_ADDRESS_RANGE,
      start,
      end
    };
    io->command(cmds, 3);
  }

  void SSD1306Driver::setDisplayStartLine(uint8_t line)
  {
    uint8_t cmd = SSD1306_CMD_DISPLAY_START_LINE | (SSD1306_VAL_DISPLAY_START_LINE & line);
    io->command(cmd);
  }

  void SSD1306Driver::setDisplayOffset(uint8_t offset)
  {
    uint8_t cmds[] = 
    {
      SSD1306_CMD_DISPLAY_OFFSET,
      offset
    };
    io->command(cmds, 2);
  }

  void SSD1306Driver::setSegmentRemapOn(bool on)
  {
    isFlippedHorizontal = on;
    uint8_t cmd = SSD1306_CMD_SEGMENT_REMAP | (on ? SSD1306_VAL_SEGMENT_REMAP : 0);
    io->command(cmd);
  }

  void SSD1306Driver::setComOutputScanDirRemapOn(bool on)
  {
    uint8_t cmd = SSD1306_CMD_COM_OUTPUT_SCAN_DIR | (on ? SSD1306_VAL_COM_OUTPUT_SCAN_DIR : 0);
    io->command(cmd);
  }

  void SSD1306Driver::setMultiplexRatio(uint8_t ratio)
  {
    uint8_t cmds[] = 
    {
      SSD1306_CMD_MULTIPLEX_RATIO,
      ratio
    };
    io->command(cmds, 2);
  }

  void SSD1306Driver::setComPinsHardwareConfig(bool alternative, bool com)
  {
    uint8_t cmds[] = 
    {
      SSD1306_CMD_COM_PINS_HARDWARE,
      (alternative ? 0b00100000 : 0) | (com ? 0b00010000 : 0) | 0x02
    };
    io->command(cmds, 2);
  }

  void SSD1306Driver::setChargePumpOn(bool on)
  {
    uint8_t cmds[] = 
    {
      SSD1306_CMD_CHARGE_PUMP_ON,
      on ? 0x14 : 0x10
    };
    io->command(cmds, 2);
  }

  void SSD1306Driver::setDisplayClockDivide(uint8_t f, uint8_t ratio)
  {
    uint8_t cmds[] = 
    {
      SSD1306_CMD_DISPLAY_CLOCK_DIVIDE,
      (static_cast<uint8_t>(f) << 4) | (ratio & 0x0F)
    };
    io->command(cmds, 2);
  }

  // Orientation
  void SSD1306Driver::flipVertical(bool flip)
  {
    setComOutputScanDirRemapOn(flip);
  }

  void SSD1306Driver::flipHorizontal(bool flip)
  {
    setSegmentRemapOn(flip);
  }

  
  /**
   * Write the screen buffer to the OLED display.
   * This is done through the write buffer interface to enable different modes of operation.
   */
  uint8_t SSD1306Driver::writeBufferByte(uint16_t pos, uint8_t byte)
  {
    uint8_t page = pos / 128;
    uint8_t col = pos % 128;
    if (page != currentPage)
    {
      setPageAddress(page);
      currentPage = page;
    }
    if (col != currentCol)
    {
      setColumnAddress(col);
      currentCol = col;
    }
    ++currentCol;
    io->data(byte);
  }

  /**
   * Write the screen buffer to the OLED display.
   * This is done through the write buffer interface to enable different modes of operation.
   */
  uint8_t SSD1306Driver::writeBufferBytes(uint16_t pos, uint8_t* byte, uint16_t len)
  {
    uint16_t toWrite;
    uint8_t page = pos / 128;
    uint8_t col = pos % 128;

    //uint8_t cmd[] = {0x20, 0, 0x21, col, 127, 0x22, page, 7};
    //io->command(cmd, 8);
    uint8_t cmd[] = {0x21, col, 127, 0x22, page, 7};
    io->command(cmd, 6);
    io->data(byte + pos, len);
  }
}
