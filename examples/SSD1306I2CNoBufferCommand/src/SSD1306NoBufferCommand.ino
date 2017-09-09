#include "devices/SSD1306I2CNoBuffer.h"
#include "fonts/Fixed8x5.h"

using namespace g3rb3n;

Fixed8x5 font;

uint8_t empty[] = {0x00};

SSD1306I2CNoBuffer oled(0x3C);
uint32_t count = 0;
uint8_t pos = 0;
bool forward = true;

void setup()
{
  setupSerial();
  setupOled();
  test();
}

void setupSerial()
{
  Serial.begin(230400);
  Serial.println();
}

void setupOled()
{
  oled.begin();
  oled.setLayout(6, 128, 0, 32);
  Serial.println("After begin");
}

void test()
{
  //oled.flipVertical(true);
  //oled.flipHorizontal(true);
  clear();
  //setChar('A', 0, 0);
  displayAlphabet();
  //oled.setHorizontalScroll(HorizontalDirection::Right, TimeInterval::_5frames, 0, 7);
  //oled.setVerticalHorizontalScroll(VerticalHorizontalDirection::VerticalRight, TimeInterval::_5frames, 0, 7, 0);
  //oled.enableScroll(true);  
}

void setFlipHorizontal()
{
  Serial.print("Flip horizontal");
  bool on = readBool();
  Serial.println(on);
  oled.flipHorizontal(on);
}

void setFlipVertical()
{
  Serial.print("Flip vertical ");
  bool on = readBool();
  Serial.println(on);
  oled.flipVertical(on);
}

void setEntireDisplay()
{
  Serial.print("Set entire display ");
  bool on = readBool();
  Serial.println(on);
  oled.setEntireDisplayOn(on);
}

void setDisplay()
{
  Serial.print("Set display on");
  bool on = readBool();
  Serial.println(on);
  oled.setDisplayOn(on);
}

void setStartLine()
{
  Serial.print("Set start line ");
  int offset = readInt();
  oled.setDisplayStartLine(offset);
}

void setDisplayOffset()
{
  Serial.print("Set display offset ");
  int offset = readInt();
  oled.setDisplayOffset(offset);
}

void setContrast()
{
  Serial.print("Set contrast ");
  int v = readInt();
  oled.setContrast(v);
}

void setInverse()
{
  Serial.print("Set inverse ");
  bool v = readBool();
  Serial.println(v);
  oled.setInverse(v);
}

void setHorizontalScroll()
{
  oled.enableScroll(false);
  Serial.print("Set horizontal scroll right ");
  bool b = readBool();
  HorizontalDirection dir = b ? HorizontalDirection::Right : HorizontalDirection::Left;
  Serial.println(b);
  Serial.print("Set horizontal scroll start page ");
  int start = readInt();
  Serial.print("Set horizontal scroll end page ");
  int end = readInt();
  oled.setHorizontalScroll(dir, TimeInterval::_5frames, start, end);
  oled.enableScroll(true);
}

void setScroll()
{
  Serial.print("Set scroll on / off ");
  bool b = readBool();
  Serial.println(b);
  oled.enableScroll(b);
}

void clear()
{
  //oled.setAddressingMode(AddressingMode::Horizontal);
  oled.setColumnRange(0,127);
  oled.setPageRange(0,7);
  for (uint16_t i = 0 ; i < 1024 ; ++i)
    oled.data(0);

  //for (uint8_t i = 0 ; i < 127 ; ++i)
  //  oled.setBitMap(0, i, empty, 8, 1);
}

void displayAlphabet()
{
  Serial.println("Display alphabet");
  setAlphabet(0);
}

void setChar(char ch, uint8_t page, uint8_t col)
{
  uint8_t cbm[5*8];
  font.get(cbm, ch);
  oled.setBitMap(empty, page, col  , 1, 1);
  oled.setBitMap(cbm  , page, col+1, 1, 5);
  oled.setBitMap(empty, page, col+6, 1, 1);
  oled.setBitMap(empty, page, col+7, 1, 1);  
}

void setAlphabet(uint8_t pos)
{
  char ch = 'A';
  for (uint8_t p = 0 ; p < 8 ; ++p)
  {
    for (uint8_t c = 0 ; c < 8 ; ++c, ++ch)
    {
      if (ch > 'Z') ch = 'A'; 
      setChar(ch, p, c*8);
    }
  }
}

void setRow()
{
  Serial.print("Page ");
  uint8_t page = readInt();
  Serial.println(page);
  Serial.print("Start ");
  uint8_t start = readInt();
  Serial.println(start);
  Serial.print("End ");
  uint8_t end = readInt();
  Serial.println(end);
  
  uint8_t bm[] = {0xFF};
  for (uint8_t i = start ; i < end ; ++i)
    oled.setBitMap(bm, page, i, 1, 1);
}

void setCol()
{
  Serial.print("Column ");
  uint8_t col = readInt();
  Serial.println(col);
  Serial.print("Start ");
  uint8_t start = readInt();
  Serial.println(start);
  Serial.print("End ");
  uint8_t end = readInt();
  Serial.println(end);
  
  uint8_t bm[] = {0xFF};
  for (uint8_t i = start ; i < end ; ++i)
    oled.setBitMap(bm, i, col, 1, 1);
}

void setLayout()
{
  Serial.print("Column offset");
  uint8_t col = readInt();
  Serial.println(col);

  Serial.print("Page offset ");
  uint8_t page = readInt();
  Serial.println(page);

  Serial.print("Columns ");
  uint8_t cols = readInt();
  Serial.println(cols);
  
  Serial.print("Pages ");
  uint8_t pages = readInt();
  Serial.println(pages);
  
  oled.setLayout(col, page, cols, pages);

}

bool readBool()
{
  Serial.print("[1|0]: ");
  while(true)
  {
    if (Serial.available() > 0) 
    {
      uint8_t c = Serial.read();
      if (c == '0')
        return false;
      if (c == '1')
        return true;
    }
  }
}

uint32_t readInt()
{
  Serial.print("[0-9]+ enter: ");
  String number;
  while(true)
  {
    if (Serial.available() > 0) 
    {
      char c = Serial.read();
      if (c == '\n')
        break;
      if(isDigit(c))
        number += c;
    }
  }
  Serial.println(number);
  return number.toInt();
}

void (*function)(void);

void printOptions()
{
  Serial.println("devhso");
}

void loop()
{
  if (Serial.available() > 0) 
  {
    uint8_t c = Serial.read();
    switch(c)
    {
      case 'c': clear(); break;
      case 'x': setContrast(); break;
      case 'i': setInverse(); break;
      case 'f': setScroll(); break;
      case 'j': setHorizontalScroll(); break;
      case 'a': displayAlphabet(); break;
      case 'd': setDisplay(); break;
      case 'e': setEntireDisplay(); break;
      case 'v': setFlipVertical(); break;
      case 'h': setFlipHorizontal(); break;
      case 's': setStartLine(); break;
      case 'o': setDisplayOffset(); break;
      case 'R': setRow(); break;
      case 'C': setCol(); break;
      case 'm': setLayout(); break;
      default: printOptions();
    }
  }
  ++count;
}
