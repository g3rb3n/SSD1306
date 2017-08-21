
#include "SSD1306Control.h"
#include "SSD1306Control_internal.h"


namespace g3rb3n
{

  /** 
   * SSD1306Control Constructor
   */
  SSD1306Control::SSD1306Control():
    rstEnabled(false)
  {
  }

  /** 
   * SSD1306Control Constructor
   * Transport only, disable reset pin functionality
   */
  SSD1306Control::SSD1306Control(ByteIO* _io):
    byteIO(_io),
    rstEnabled(false)
  {
  }

  SSD1306Control::SSD1306Control(ByteIO* _io, uint8_t _rstPin):
    byteIO(_io),
    rstPin(_rstPin),
    rstEnabled(true) 
  {
  }

  SSD1306Control::~SSD1306Control()
  {
  }

  /*
  void SSD1306Control::restOrg()
  {
    // Display Init sequence for 64x48 OLED module
    command(DISPLAYOFF);      // 0xAE

    //Display Clock Divide Ratio (D)(A[3:0])
    //Set the divide ratio to generate DCLK (Display Clock) from CLK. 
    //The divide ratio is from 1 to 16, with reset value = 1. 
    //Oscillator Frequency (A[7:4])
    //Program the oscillator frequency Fosc that is the source of CLK if CLS pin is pulled high. 
    //The 4-bit value results in 16 different frequency settings available as shown below.
    //The default setting is 1000b.
    command(SETDISPLAYCLOCKDIV);  // 0xD5
    command(0x81);

    command(SETMULTIPLEX);      // 0xA8
    command(0x2F);

    command(SETDISPLAYOFFSET);    // 0xD3
    command(0x0);          // no offset

    command(SETSTARTLINE | 0x0);  // line #0

    command(CHARGEPUMP);      // enable charge pump
    command(0x14);

    command(NORMALDISPLAY);      // 0xA6
    
    command(DISPLAYALLONRESUME);  // 0xA4

    command(SEGREMAP | 0x1);
    command(COMSCANDEC);

    command(SETCOMPINS);      // 0xDA
    command(0x12);

    command(SETCONTRAST);      // 0x81
    command(0x8F);

    //A[3:0] : Phase 1 period of up to 15 DCLK
    //clocks 0 is invalid entry
    //(RESET=2h)
    //A[7:4] : Phase 2 period of up to 15 DCLK
    //clocks 0 is invalid entry
    //(RESET=2h )
    command(SETPRECHARGE);      // 0xd9
    //command(0xF1);
    command(0x22);

    //A[6:4]   Hex    V COMH deselect level
    //000b     00h    ~ 0.65 x VCC
    //010b     20h    ~ 0.77 x VCC (RESET)
    //011b     30h    ~ 0.83 x VCC
    command(SETVCOMDESELECT);      // 0xDB
    command(0x20);

    command(DISPLAYON);        //--turn on oled panel
    
  }
  */
  /** 
   * Initialisation of SSD1306Control Library.
   */
  void SSD1306Control::begin()
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
    command(0xA8);
    command(0x3F);

    //Set Display Offset D3h, 00h 
    command(0xD3);
    command(0x00);

    //Set Display Start Line 40h
    command(0x40);

    //Set Segment re-map A0h/A1h
    command(0xA0);

    //Set COM Output Scan Direction C0h/C8h
    command(0xC0);

    //Set Contrast Control  81h, 7Fh
    command(0x81);
    command(0x7F);

    //Disable Entire Display On A4h
    command(0xA4);

    //Set Normal Display A6h
    command(0xA6);

    //Set Osc Frequency D5h, 80h
    command(0xD5);
    command(0x80);

    //Set COM Pins hardware configuration DAh, 02 
    command(0xDA);
  //  command(0x02);
    command(0x12);

    //Enable charge pump regulator 8Dh, 14h
    command(0x8D);
    command(0x14);

    //Display On AFh
    command(0xAF);
    
    //Ser page addressing mode
    command(0x20);
    command(0x02);
    
  }

  /** \brief Send the display a command byte

      Send a command via SPI, I2C or parallel  to SSD1306Control controller.
    For SPI we set the DC and CS pins here, and call spiTransfer(byte)
    to send the data. For I2C and Parallel we use the write functions
    defined in hardware.cpp to send the data.
  */
  void SSD1306Control::command(uint8_t c)
  {
    byteIO->write(I2C_COMMAND, c);
  }

  /** \brief Send the display a data byte

      Send a data byte via SPI, I2C or parallel to SSD1306Control controller.
    For SPI we set the DC and CS pins here, and call spiTransfer(byte)
    to send the data. For I2C and Parallel we use the write functions
    defined in hardware.cpp to send the data.
  */
  void SSD1306Control::data(uint8_t c)
  {
    byteIO->write(I2C_DATA, c);
  }

  /** \brief Set SSD1306Control page address.

      Send page address command and address to the SSD1306Control OLED controller.
  */
//  #define DEBUG
  void SSD1306Control::setPageAddress(uint8_t page)
  {
    #ifdef DEBUG
    Serial.print("setPageAddress:");
    Serial.print(page);
    Serial.print(' ');
    Serial.print(page, 16);
    Serial.println();
    #endif
    command(SSD1306_CMD_SET_PAGE_START | page);
  }

  /** \brief Set SSD1306Control column address.

      Send column address command and address to the SSD1306Control OLED controller.
  */
  void SSD1306Control::setColumnAddress(uint8_t col)
  {
    uint8_t high = col >> 4;
    uint8_t low  = col & 0x0F;
    #ifdef DEBUG
    Serial.print("setColumnAddress:");
    Serial.print(col);
    Serial.print(' ');
    Serial.print(col, 16);
    Serial.println();
      
    Serial.print("H:");
    Serial.print(high, 16);
    Serial.print(' ');
    #endif
    low |= SSD1306_CMD_SET_COLUMN_NIBBLE_H;
    //high |= SSD1306_CMD_SET_COLUMN_NIBBLE_L;
    #ifdef DEBUG
    Serial.print(high, 16);
    Serial.println();
    Serial.print("L:");
    Serial.print(low, 16);
    Serial.print(' ');
    #endif
    high |= SSD1306_CMD_SET_COLUMN_NIBBLE_L;
    //low |= SSD1306_CMD_SET_COLUMN_NIBBLE_H;
    #ifdef DEBUG
    Serial.print(low, 16);
    Serial.println();
    #endif
    command(low);
    command(high);
  }
#undef DEBUG

  /** \brief Invert display.

      The WHITE color of the display will turn to BLACK and the BLACK will turn to WHITE.
  */
  void SSD1306Control::invert(boolean inv)
  {
    if (inv)
      command(INVERTDISPLAY);
    else
      command(NORMALDISPLAY);
  }

  /** \brief Set contrast.

      OLED contract value from 0 to 255. Note: Contrast level is not very obvious.
  */
  void SSD1306Control::contrast(uint8_t contrast)
  {
    command(SETCONTRAST);      // 0x81
    command(contrast);
  }

  /** \brief Stop scrolling.

      Stop the scrolling of graphics on the OLED.
  */
  void SSD1306Control::scrollStop(void)
  {
    command(DEACTIVATESCROLL);
  }

  /** \brief Right scrolling.

  Set row start to row stop on the OLED to scroll right. 
  Refer to http://learn.microview.io/intro/general-overview-of-microview.html for explanation of the rows.
  */
  void SSD1306Control::scrollRight(uint8_t start, uint8_t stop)
  {
    // stop must be larger or equal to start
    if (stop<start)  return;

    scrollStop();    // need to disable scrolling before starting to avoid memory corrupt
    command(RIGHTHORIZONTALSCROLL);
    command(0x00);
    command(start);
    command(0x7);    // scroll speed frames , TODO
    command(stop);
    command(0x00);
    command(0xFF);
    command(ACTIVATESCROLL);
  }

  /** \brief Vertical flip.

  Flip the graphics on the OLED vertically.
  */
  void SSD1306Control::flipVertical(boolean flip) {
    if (flip) {
      command(COMSCANINC);
    }
    else {
      command(COMSCANDEC);
    }
  }

  /** \brief Horizontal flip.

      Flip the graphics on the OLED horizontally.
  */
  void SSD1306Control::flipHorizontal(boolean flip) {
    if (flip) {
      command(SEGREMAP | 0x0);
    }
    else {
      command(SEGREMAP | 0x1);
    }
  }

  /*
    Return a pointer to the start of the RAM screen buffer for direct access.
  */
  //uint8_t* SSD1306Control::getScreenBuffer(void) {
  //  return screenmemory;
  //}

  /*
  Draw Bitmap image on screen. 
  The array for the bitmap can be stored in the Arduino file, so user don't have to mess with the library files.
  To use, create uint8_t array that is LCDWIDTHxLCDHEIGHT/8 pixels. Then call .drawBitmap and pass it the array.
  */
  /*
  void SSD1306Control::drawBitmap(uint8_t * bitArray)
  {
    for (int i=0; i<(width * height / 8); i++)
      memory->write(i, bitArray[i]);
  }
  */

  void SSD1306Control::display(ScreenBuffer& buffer)
  {
    writeBuffer(buffer.screenBuffer(), buffer.size);
  }

  void SSD1306Control::display(ScreenBuffer& buffer, uint8_t minX, uint8_t minY, uint8_t maxX, uint8_t maxY)
  {
    writeBuffer(buffer.screenBuffer(), buffer.size, minX, minY, maxX, maxY);
  }

  void SSD1306Control::writeBuffer(uint8_t* buffer, uint16_t size)
  {
    uint8_t i, j;

    for (i = 0 ; i < pages ; ++i)
    {
      setPageAddress(i);
      setColumnAddress(0);
      for (j = 0 ; j < columns ; j++)
      {
        data(buffer[ i * columns + j ]);
      }
    }
  }

  uint8_t SSD1306Control::writeBufferByte(uint16_t pos, uint8_t byte)
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
    data(byte);
  }

  void SSD1306Control::writeBuffer(uint8_t* buffer, uint16_t size, uint8_t minX, uint8_t minY, uint8_t maxX, uint8_t maxY)
  {
    uint8_t i, j;
    uint8_t startPage = minY / 8;
    uint8_t endPage = maxY / 8;
    uint8_t startCol = minX;
    uint8_t endCol = maxX;
    #ifdef DEBUG
    Serial.println(startPage);
    Serial.println(endPage);
    Serial.println(startCol);
    Serial.println(endCol);
    #endif
    startCol = 0;
    for (i = startPage ; i <= endPage ; ++i)
    {
      setPageAddress(i);
      setColumnAddress(startCol);
      for (j = startCol ; j <= endCol ; ++j)
      {
        data(buffer[ i * columns + j ]);
      }
    }
  }

}
