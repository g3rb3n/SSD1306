#include "devices/SSD1306I2CNoBuffer.h"
#include "fonts/Fixed8x5.h"

using namespace g3rb3n;

Fixed8x5 font;

uint8_t cols = 5;
uint8_t rows = 8;
uint8_t bitmap[5*8];


uint8_t empty[] = {
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00
};

SSD1306I2CNoBuffer oled(0x3C);
uint32_t count = 0;
uint8_t pos = 0;
bool forward = true;

void setup()
{
  setupSerial();
  setupOled();
  setupFont();
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
  Serial.println("After begin");
}

void setupFont()
{
  uint8_t bm[5];
  for (char c = 'A' ; c < 'I' ; ++c)
  {
    font.get(bm, c);
    for(uint8_t i = 0; i < 5 ; ++i)
    {
      bitmap[(c - 'A') * 5 + i] = bm[i];
    }
  }
}

void test()
{
  oled.flipVertical(true);
  oled.flipHorizontal(true);
  clear();
  setAlphabet(0);
  //oled.setHorizontalScroll(HorizontalDirection::Right, TimeInterval::_5frames, 0, 7);
  oled.setVerticalHorizontalScroll(VerticalHorizontalDirection::VerticalRight, TimeInterval::_5frames, 0, 7, 0);
  oled.enableScroll(true);  
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
  setAlphabet(0);
  //setAlphabet(60);
  //setAlphabet(120);
}

void setAlphabet(uint8_t pos)
{
  oled.setBitMap(0, pos, empty, 8, 1);
  oled.setBitMap(0, pos+1, bitmap, rows, cols);
  oled.setBitMap(0, pos+cols+1, empty, 8, 1);  
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
      default: printOptions();
    }
  }
  ++count;
}
