#ifndef _SSD1306_INTERNAL_H_
#define _SSD1306_INTERNAL_H_

#include <stdio.h>
#include <Arduino.h>

#define I2C_ADDRESS_SA0_0 0b0111100
#define I2C_ADDRESS_SA0_1 0b0111101
#define I2C_COMMAND 0x00
#define I2C_DATA 0x40

#define SSD1306_CMD_SET_PAGE_START  0xB0
#define SSD1306_CMD_SET_COLUMN_NIBBLE_H 0x00
#define SSD1306_CMD_SET_COLUMN_NIBBLE_L 0x10

#define SETCONTRAST                 0x81
#define DISPLAYALLONRESUME          0xA4
#define DISPLAYALLON                0xA5
#define DISPLAYOFF                  0xAE
#define DISPLAYON                   0xAF

// Scroll
#define RIGHTHORIZONTALSCROLL       0x26
#define LEFT_HORIZONTALSCROLL       0x27
#define SCROLL_A_DUMMY              0x00
#define SCROLL_B_START_PAGE0        0x00
#define SCROLL_B_START_PAGE1        0x01
#define SCROLL_B_START_PAGE2        0x02
#define SCROLL_B_START_PAGE3        0x03
#define SCROLL_B_START_PAGE4        0x04
#define SCROLL_B_START_PAGE5        0x05
#define SCROLL_B_START_PAGE6        0x06
#define SCROLL_B_START_PAGE7        0x07
#define SCROLL_C_INTERVAL_5         0x00
#define SCROLL_C_INTERVAL_64        0x01
#define SCROLL_C_INTERVAL_128       0x02
#define SCROLL_C_INTERVAL_256       0x03
#define SCROLL_C_INTERVAL_3         0x04
#define SCROLL_C_INTERVAL_4         0x05
#define SCROLL_C_INTERVAL_25        0x06
#define SCROLL_C_INTERVAL_2         0x07
#define SCROLL_D_END_PAGE_0         0x00
#define SCROLL_D_END_PAGE_1         0x01
#define SCROLL_D_END_PAGE_2         0x02
#define SCROLL_D_END_PAGE_3         0x03
#define SCROLL_D_END_PAGE_4         0x04
#define SCROLL_D_END_PAGE_5         0x05
#define SCROLL_D_END_PAGE_6         0x06
#define SCROLL_D_END_PAGE_7         0x07
#define SCROLL_E_DUMMY              0x00
#define SCROLL_F_DUMMY              0xFF


#define ACTIVATESCROLL              0x2F
#define DEACTIVATESCROLL            0x2E

#define SETVERTICALSCROLLAREA 			0xA3
#define VERTICALRIGHTHORIZONTALSCROLL	0x29
#define VERTICALLEFTHORIZONTALSCROLL	0x2A


#define SETLOWCOLUMN                0x00
#define SETHIGHCOLUMN               0x10

#define SET_MEM_ADDR_MODE           0x20
#define SET_MEM_ADDR_MODE_H         0x00
#define SET_MEM_ADDR_MODE_V         0x01
#define SET_MEM_ADDR_MODE_P         0x02

#define SET_COLUMN_ADDRESS          0x21
#define SET_COLUMN_ADDRESS_A_START  0x00
#define SET_COLUMN_ADDRESS_B_END    0x00

#define SET_PAGE_ADDRESS            0x22
#define SET_PAGE_ADDRESS_A_START    0x00
#define SET_PAGE_ADDRESS_B_END      0x00

#define SET_PAGE_START_ADDRESS      0xB0

#define SETSTARTLINE                0x40
#define SETSTARTLINE_MASK           0x3F

#define SETSEGMENT_REMAP_0          0xA0
#define SETSEGMENT_REMAP_127        0xA1

#define SETMULTIPLEX_RATIO          0xA8

//TODO REST
#define NORMALDISPLAY 		0xA6
#define INVERTDISPLAY 		0xA7
#define SETDISPLAYOFFSET 	0xD3
#define SETCOMPINS 			0xDA
#define SETVCOMDESELECT		0xDB
#define SETDISPLAYCLOCKDIV 	0xD5
#define SETPRECHARGE 		0xD9
#define SETMULTIPLEX 		0xA8
#define MEMORYMODE 			0x20
#define COMSCANINC 			0xC0
#define COMSCANDEC 			0xC8
#define SEGREMAP 			0xA0
#define CHARGEPUMP 			0x8D
#define EXTERNALVCC 		0x01
#define SWITCHCAPVCC 		0x02


typedef enum CMD {
	CMD_CLEAR,			//0
	CMD_INVERT,			//1
	CMD_CONTRAST,		//2
	CMD_DISPLAY,		//3
	CMD_SETCURSOR,		//4
	CMD_PIXEL,			//5
	CMD_LINE,			//6
	CMD_LINEH,			//7
	CMD_LINEV,			//8
	CMD_RECT,			//9
	CMD_RECTFILL,		//10
	CMD_CIRCLE,			//11
	CMD_CIRCLEFILL,		//12
	CMD_DRAWCHAR,		//13
	CMD_DRAWBITMAP,		//14
	CMD_GETLCDWIDTH,	//15
	CMD_GETLCDHEIGHT,	//16
	CMD_SETCOLOR,		//17
	CMD_SETDRAWMODE		//18
} commCommand_t;

#endif
