/****************************************************************************** 
font5x7.h
Definition for small font

This file was imported from the MicroView library, written by GeekAmmo
(https://github.com/geekammo/MicroView-Arduino-Library), and released under 
the terms of the GNU General Public License as published by the Free Software 
Foundation, either version 3 of the License, or (at your option) any later 
version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Modified by:
Emil Varughese @ Edwin Robotics Pvt. Ltd.
July 27, 2015
https://github.com/emil01/SparkFun_Micro_OLED_Arduino_Library/

******************************************************************************/
#ifndef _Fixed8x5_H_
#define _Fixed8x5_H_

#include "Fixed.h"

#if defined(__AVR__) || defined(__arm__)
  #include <avr/pgmspace.h>
#else
  #include <pgmspace.h>
#endif

/** 
 * The Fixed class provides a generic interface fixed width fonts.
 */
namespace g3rb3n
{

  class Fixed8x5 : public Fixed
  {
    private:
      static const uint8_t chars[] PROGMEM;
    public:
      uint8_t width() const
      {
        return 5;
      }
      
      uint8_t height() const
      {
        return 8;
      }

      uint8_t size() const
      {
        return 5;
      }

      void get(uint8_t*, char c) const;
      bool has(char c) const;
      
  };

}

#endif
