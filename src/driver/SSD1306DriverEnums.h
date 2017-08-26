#ifndef _SSD1306DriverEnums_H_
#define _SSD1306DriverEnums_H_

#include "../util/types.h"

enum class AddressingMode : uint8_t
{
  Horizontal = 0x00,
  Vertical,
  Page
};

enum class HorizontalDirection : uint8_t
{
  Right,
  Left
};

enum class TimeInterval : uint8_t
{
  _5frames,
  _64frames,
  _128frames,
  _256frames,
  _3frames,
  _4frames,
  _25frames,
  _2frames
};

enum class VerticalHorizontalDirection : uint8_t
{
  VerticalRight = 1,
  VerticalLeft = 2
};

#endif
