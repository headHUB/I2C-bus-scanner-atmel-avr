#include <avr/pgmspace.h>  // PROGMEM

// ST7735 Commands
#define SWRESET 0x01    // software reset loads all default values to registers and 120ms to complete
#define RDDID 0x04      // read display ID
#define RDDST 0x09      // read display status
#define RDDPM 0x0A      // read display power mode
#define RDDMADCTL 0x0B  // read display memory access control register 
#define RDDCOLMOD 0x0C  // read display pixel format
#define RDDIM 0x0D      // read display image mode
#define RDDSM 0x0E      // read display signal mode
#define SLPIN 0x10      // sleep in (enter minimum power conumption mode)
#define SLPOUT 0x11     // sleep out
#define PTLON 0x12      // partial display mode on
#define NORON 0x13      // normal display mode on
#define INVOFF 0x20     // display inversion off
#define INVON 0x21      // display inversion on
#define GAMSET 0x26     // select desired Gamma curve
#define DISPOFF 0x28    // display off
#define DISPON 0x29     // display on
#define CASET 0x2A      // column address set
#define RASET 0x2B      // row address set
#define RAMWR 0x2C      // RAM write
#define RAMRD 0x2E      // RAM read
#define PTLAR 0x30      // define partial mode display area
#define TEOFF 0x34      // tearing effect line off
#define TEON 0x35       // tearing effect line on
#define MADCTL 0x36     // axis control
#define IDMOFF 0x38     // idle mode off
#define IDMON 0x39      // idle mode on
#define COLMOD 0x3A     // interface pixel format
#define FRMCTR1 0xB1
#define FRMCTR2 0xB2
#define FRMCTR3 0xB3
#define INVCTR  0xB4
#define DISSET5 0xB6
#define PWCTR1  0xC0
#define PWCTR2  0xC1
#define PWCTR3  0xC2
#define PWCTR4  0xC3
#define PWCTR5  0xC4
#define VMCTR1  0xC5
#define RDID1 0xDA      // read ID1 value
#define RDID2 0xDB      // read ID2 value
#define RDID3 0xDC      // read ID3 value
#define RDID4 0xDD      // read ID4 value
#define PWCTR6  0xFC
#define GMCTRP1 0xE0
#define GMCTRN1 0xE1

// 1.44" (128x128) TFT display constants
#define XSIZE 131
#define YSIZE 131
#define XMAX XSIZE-1
#define YMAX YSIZE-1

// Colors 16-bit/pixel: RGB=(565) Pixel Color Format (Color Depth)
#define White   0xFFFF     /* 31, 63, 31 */
#define Black 	0x0000     /*  0,  0,  0 */
#define Red 	0xF800     /* 31,  0,  0 */
#define Green 	0x07E0     /*  0, 63,  0 */
#define Blue 	0x001F     /*  0,  0, 31 */
#define Cyan  	0x07FF     /*  0, 63, 31 */
#define Magenta 0xF81F     /* 31,  0, 31 */
#define Yellow 	0xFFE0     /* 31, 63,  0 */
// Color Gradient RGB-565  /*  R,  G,  B */
#define UVB330 0x7B2F      /* 15, 25, 15 */
#define Violet380 0x580B   /* 10,  0, 10 */
#define Violet381 0x500A   /* 11,  0, 11 */
#define Violet382 0x600C   /* 12,  0, 12 */
#define Violet385 0x680E   /* 13,  0, 14 */
#define Violet387 0x7010   /* 14,  0, 16 */
#define Violet390 0x7811   /* 15,  0, 17 */
#define Violet395 0x8014   /* 16,  0, 20 */
#define Violet397 0x8815   /* 17,  0, 21 */
#define Violet400 0x9016   /* 18,  0, 22 */
#define Violet402 0x8818   /* 17,  0, 24 */
#define Violet405 0x8019   /* 16,  0, 25 */
#define Violet410 0x781B   /* 15,  0, 27 */
#define Violet415 0x701D   /* 14,  0, 29 */
#define Violet420 0x681F   /* 13,  0, 31 */
#define Violet422 0x601F   /* 12,  0, 31 */
#define Violet425 0x501F   /* 10,  0, 31 */
#define Blue429   0x403F   /*  8,  0, 31 */
#define Blue431   0x303F   /*  6,  0, 31 */
#define Blue435   0x201F   /*  4,  0, 31 */
#define Blue437   0x101F   /*  2,  0, 31 */
#define Blue440   0x001F   /*  0,  0, 31 */
#define Blue441   0x005F   /*  0,  2, 31 */
#define Blue442   0x009F   /*  0,  4, 31 */
#define Blue443   0x00DF   /*  0,  6, 31 */
#define Blue444   0x011F   /*  0,  8, 31 */
#define Blue445   0x015F   /*  0, 10, 31 */
#define Blue447   0x01BF   /*  0, 13, 31 */
#define Blue448   0x01FF   /*  0, 15, 31 */
#define Blue450   0x023F   /*  0, 17, 31 */
#define Blue452   0x029F   /*  0, 20, 31 */
#define Blue455   0x02FF   /*  0, 23, 31 */
#define Blue457   0x037F   /*  0, 27, 31 */
#define Cyan460   0x03DF   /*  0, 30, 31 */
#define Cyan462   0x043F   /*  0, 33, 31 */
#define Cyan465   0x049F   /*  0, 36, 31 */
#define Cyan467   0x04FF   /*  0, 39, 31 */
#define Cyan470   0x055F   /*  0, 42, 31 */
#define Cyan472   0x05BF   /*  0, 45, 31 */
#define Cyan475   0x061F   /*  0, 48, 31 */
#define Cyan480   0x06BF   /*  0, 53, 31 */
#define Cyan485   0x075F   /*  0, 58, 31 */
#define Cyan490   0x07FF   /*  0, 63, 31 */
#define Cyan492   0x07FC   /*  0, 63, 28 */
#define Cyan495   0x07F9   /*  0, 63, 25 */
#define Cyan497   0x07F6   /*  0, 63, 22 */
#define Cyan500   0x07F2   /*  0, 63, 18 */
#define Cyan502   0x07EE   /*  0, 63, 14 */
#define Cyan505   0x07EA   /*  0, 63, 10 */
#define Green507  0x07E7   /*  0, 63,  7 */
#define Green508  0x07E5   /*  0, 63,  5 */
#define Green509  0x07E3   /*  0, 63,  2 */
#define Green510  0x07E0   /*  0, 63,  0 */
#define Green515  0x1FE0   /*  3, 63,  0 */
#define Green520  0x37E0   /*  6, 63,  0 */
#define Green525  0x4FE0   /*  9, 63,  0 */
#define Green530  0x5FE0   /* 11, 63,  0 */
#define Green535  0x77E0   /* 14, 63,  0 */
#define Green540  0x87E0   /* 16, 63,  0 */
#define Green545  0x97E0   /* 18, 63,  0 */
#define Green550  0xA7E0   /* 20, 63,  0 */
#define Yellow555  0xB7E0  /* 22, 63,  0 */
#define Yellow560  0xC7E0  /* 24, 63,  0 */
#define Yellow565  0xD7E0  /* 26, 63,  0 */
#define Yellow570  0xE7E0  /* 28, 63,  0 */
#define Yellow575 0xF7E0   /* 30, 63,  0 */
#define Yellow580 0xFFE0   /* 31, 63,  0 */
#define Yellow585 0xFF60   /* 31, 59,  0 */
#define Yellow590 0xFEE0   /* 31, 55,  0 */
#define Yellow595 0xFE60   /* 31, 51,  0 */
#define Yellow600 0xFDE0   /* 31, 47,  0 */
#define Yellow605 0xFD60   /* 31, 43,  0 */
#define Yellow607 0xFD20   /* 31, 41,  0 */
#define Orange610 0xFCC0   /* 31, 38,  0 */
#define Orange615 0xFC40   /* 31, 34,  0 */
#define Orange617 0xFBE0   /* 31, 31,  0 */
#define Orange620 0xFBA0   /* 31, 29,  0 */
#define Orange622 0xFB60   /* 31, 27,  0 */
#define Orange625 0xFB00   /* 31, 24,  0 */
#define Orange627 0xFAC0   /* 31, 22,  0 */
#define Orange630 0xFA60   /* 31, 19,  0 */
#define Orange632 0xFA20   /* 31, 17,  0 */
#define Orange635 0xF9C0   /* 31, 14,  0 */
#define Orange637 0xF980   /* 31, 12,  0 */
#define Orange640 0xF900   /* 31,  8,  0 */
#define Orange642 0xF880   /* 31,  4,  0 */
#define Red645    0xF800   /* 31,  0,  0 */
// #define Red650    0xF800
// #define Red655    0xF800
// #define Red660    0xF800
// #define Red665    0xF800
// #define Red670    0xF800
// #define Red675    0xF800  // 645-700nm all true red per RGB=(565) 
// #define Red680    0xF800
// #define Red685    0xF800
// #define Red690    0xF800
// #define Red695    0xF800
// #define Red700    0xF800
#define Red705    0xF000   /* 30,  0,  0 */
#define Red710    0xE800   /* 29,  0,  0 */
#define Red715    0xE000   /* 28,  0,  0 */
#define Red720    0xD800   /* 27,  0,  0 */
#define Red725    0xD000   /* 26,  0,  0 */
#define Red730    0xC800   /* 25,  0,  0 */
#define Red735    0xB800   /* 23,  0,  0 */
#define Red740    0xB000   /* 22,  0,  0 */
#define Red745    0xA800   /* 21,  0,  0 */
#define Red750    0xA000   /* 20,  0,  0 */
#define Red755    0x9000   /* 18,  0,  0 */
#define Red760    0x8800   /* 17,  0,  0 */
#define Red765    0x8000   /* 16,  0,  0 */
#define Red770    0x7000   /* 14,  0,  0 */
#define Red775    0x6800   /* 13,  0,  0 */
#define Red780    0x6000   /* 12,  0,  0 */
#define nearIR850 0x8A69   /* 15, 19,  9 */

// Characters
const uint8_t font5x7[96][5] PROGMEM =
{
 { 0x00, 0x00, 0x00, 0x00, 0x00 },  // (space)
 { 0x00, 0x00, 0x5F, 0x00, 0x00 },  // !
 { 0x00, 0x07, 0x00, 0x07, 0x00 },  // "
 { 0x14, 0x7F, 0x14, 0x7F, 0x14 },  // #
 { 0x24, 0x2A, 0x7F, 0x2A, 0x12 },  // $
 { 0x23, 0x13, 0x08, 0x64, 0x62 },  // %
 { 0x36, 0x49, 0x55, 0x22, 0x50 },  // &
 { 0x00, 0x05, 0x03, 0x00, 0x00 },  // '
 { 0x00, 0x1C, 0x22, 0x41, 0x00 },  // (
 { 0x00, 0x41, 0x22, 0x1C, 0x00 },  // )
 { 0x08, 0x2A, 0x1C, 0x2A, 0x08 },  // *
 { 0x08, 0x08, 0x3E, 0x08, 0x08 },  // +
 { 0x00, 0x50, 0x30, 0x00, 0x00 },  // ,
 { 0x08, 0x08, 0x08, 0x08, 0x08 },  // -
 { 0x00, 0x60, 0x60, 0x00, 0x00 },  // .
 { 0x20, 0x10, 0x08, 0x04, 0x02 },  // /
 { 0x3E, 0x51, 0x49, 0x45, 0x3E },  // 0
 { 0x00, 0x42, 0x7F, 0x40, 0x00 },  // 1
 { 0x42, 0x61, 0x51, 0x49, 0x46 },  // 2
 { 0x21, 0x41, 0x45, 0x4B, 0x31 },  // 3
 { 0x18, 0x14, 0x12, 0x7F, 0x10 },  // 4
 { 0x27, 0x45, 0x45, 0x45, 0x39 },  // 5
 { 0x3C, 0x4A, 0x49, 0x49, 0x30 },  // 6
 { 0x01, 0x71, 0x09, 0x05, 0x03 },  // 7
 { 0x36, 0x49, 0x49, 0x49, 0x36 },  // 8
 { 0x06, 0x49, 0x49, 0x29, 0x1E },  // 9
 { 0x00, 0x36, 0x36, 0x00, 0x00 },  // :
 { 0x00, 0x56, 0x36, 0x00, 0x00 },  // ;
 { 0x00, 0x08, 0x14, 0x22, 0x41 },  // <
 { 0x14, 0x14, 0x14, 0x14, 0x14 },  // =
 { 0x41, 0x22, 0x14, 0x08, 0x00 },  // >
 { 0x02, 0x01, 0x51, 0x09, 0x06 },  // ?
 { 0x32, 0x49, 0x79, 0x41, 0x3E },  // @
 { 0x7E, 0x11, 0x11, 0x11, 0x7E },  // A
 { 0x7F, 0x49, 0x49, 0x49, 0x36 },  // B
 { 0x3E, 0x41, 0x41, 0x41, 0x22 },  // C
 { 0x7F, 0x41, 0x41, 0x22, 0x1C },  // D
 { 0x7F, 0x49, 0x49, 0x49, 0x41 },  // E
 { 0x7F, 0x09, 0x09, 0x01, 0x01 },  // F
 { 0x3E, 0x41, 0x41, 0x51, 0x32 },  // G
 { 0x7F, 0x08, 0x08, 0x08, 0x7F },  // H
 { 0x00, 0x41, 0x7F, 0x41, 0x00 },  // I
 { 0x20, 0x40, 0x41, 0x3F, 0x01 },  // J
 { 0x7F, 0x08, 0x14, 0x22, 0x41 },  // K
 { 0x7F, 0x40, 0x40, 0x40, 0x40 },  // L
 { 0x7F, 0x02, 0x04, 0x02, 0x7F },  // M
 { 0x7F, 0x04, 0x08, 0x10, 0x7F },  // N
 { 0x3E, 0x41, 0x41, 0x41, 0x3E },  // O
 { 0x7F, 0x09, 0x09, 0x09, 0x06 },  // P
 { 0x3E, 0x41, 0x51, 0x21, 0x5E },  // Q
 { 0x7F, 0x09, 0x19, 0x29, 0x46 },  // R
 { 0x46, 0x49, 0x49, 0x49, 0x31 },  // S
 { 0x01, 0x01, 0x7F, 0x01, 0x01 },  // T
 { 0x3F, 0x40, 0x40, 0x40, 0x3F },  // U
 { 0x1F, 0x20, 0x40, 0x20, 0x1F },  // V
 { 0x7F, 0x20, 0x18, 0x20, 0x7F },  // W
 { 0x63, 0x14, 0x08, 0x14, 0x63 },  // X
 { 0x03, 0x04, 0x78, 0x04, 0x03 },  // Y
 { 0x61, 0x51, 0x49, 0x45, 0x43 },  // Z
 { 0x00, 0x00, 0x7F, 0x41, 0x41 },  // [
 { 0x02, 0x04, 0x08, 0x10, 0x20 },  // "\"
 { 0x41, 0x41, 0x7F, 0x00, 0x00 },  // ]
 { 0x04, 0x02, 0x01, 0x02, 0x04 },  // ^
 { 0x40, 0x40, 0x40, 0x40, 0x40 },  // _
 { 0x00, 0x01, 0x02, 0x04, 0x00 },  // `
 { 0x20, 0x54, 0x54, 0x54, 0x78 },  // a
 { 0x7F, 0x48, 0x44, 0x44, 0x38 },  // b
 { 0x38, 0x44, 0x44, 0x44, 0x20 },  // c
 { 0x38, 0x44, 0x44, 0x48, 0x7F },  // d
 { 0x38, 0x54, 0x54, 0x54, 0x18 },  // e
 { 0x08, 0x7E, 0x09, 0x01, 0x02 },  // f
 { 0x08, 0x14, 0x54, 0x54, 0x3C },  // g
 { 0x7F, 0x08, 0x04, 0x04, 0x78 },  // h
 { 0x00, 0x44, 0x7D, 0x40, 0x00 },  // i
 { 0x20, 0x40, 0x44, 0x3D, 0x00 },  // j
 { 0x00, 0x7F, 0x10, 0x28, 0x44 },  // k
 { 0x00, 0x41, 0x7F, 0x40, 0x00 },  // l
 { 0x7C, 0x04, 0x18, 0x04, 0x78 },  // m
 { 0x7C, 0x08, 0x04, 0x04, 0x78 },  // n
 { 0x38, 0x44, 0x44, 0x44, 0x38 },  // o
 { 0x7C, 0x14, 0x14, 0x14, 0x08 },  // p
 { 0x08, 0x14, 0x14, 0x18, 0x7C },  // q
 { 0x7C, 0x08, 0x04, 0x04, 0x08 },  // r
 { 0x48, 0x54, 0x54, 0x54, 0x20 },  // s
 { 0x04, 0x3F, 0x44, 0x40, 0x20 },  // t
 { 0x3C, 0x40, 0x40, 0x20, 0x7C },  // u
 { 0x1C, 0x20, 0x40, 0x20, 0x1C },  // v
 { 0x3C, 0x40, 0x30, 0x40, 0x3C },  // w
 { 0x44, 0x28, 0x10, 0x28, 0x44 },  // x
 { 0x0C, 0x50, 0x50, 0x50, 0x3C },  // y
 { 0x44, 0x64, 0x54, 0x4C, 0x44 },  // z
 { 0x00, 0x08, 0x36, 0x41, 0x00 },  // {
 { 0x00, 0x00, 0x7F, 0x00, 0x00 },  // |
 { 0x00, 0x41, 0x36, 0x08, 0x00 },  // }
 { 0x08, 0x08, 0x2A, 0x1C, 0x08 },  // ->
 { 0x08, 0x1C, 0x2A, 0x08, 0x08 },  // <-
};

// TFT LCD Functions (ST7735)
uint8_t serialTransfer(uint8_t data){
	SPDR = data;             // write data to SPI Data Register (SPDR)
	while (!(SPSR & 0x80));  // wait until SPI Interrupt Flag (SPIF) is set in the SPI Status Register (SPSR) indicating the transfer is complete
	return SPDR;             // return data received from slave (SPI is full duplex ignore if slave response if its not applicable)
}

void writeByte (uint8_t b){
	serialTransfer(b);  // write byte (8 bits)
}

void writeWord (uint16_t w){
	serialTransfer(w >> 8);    // write upper byte (8 bits)
	serialTransfer(w & 0xFF);  // write lower byte (8 bits)
}

void writeCmd (uint8_t cmd){
	PORTB &= ~(1<<PORTB1);  // D/C  0=command, 1=data
	serialTransfer(cmd);
	PORTB |= (1<<PORTB1);   // return DC high
}

void setOrientation(uint16_t degrees){
	uint8_t arg;
	switch (degrees){                 // Set the display orientation to 0,90,180,or 270 degrees
		case 90:  arg = 0x68; break;  // IF LSB = 0 --> RGB
		case 180: arg = 0xC8; break;  // IF LSB = 8 --> BGR
		case 270: arg = 0xA8; break;
		default:  arg = 0x08; break;
	}
	writeCmd(MADCTL);
	writeByte(arg);
}

void write565 (uint16_t data, uint16_t count){  // 16-bit/pixel: RGB=(565) Pixel Color Format (Color Depth)
	writeCmd(RAMWR);             // note: inlined spi serialTransfer for optimization
	for (;count>0;count--){
		SPDR = (data >> 8);      // write hi byte data & 0x00FF
		while (!(SPSR & 0x80));  // wait for transfer to complete
		SPDR = (data & 0xFF);    // write lo byte
		while (!(SPSR & 0x80));  // wait for transfer to complete
	}
}

void setAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
	writeCmd(CASET);  // column address set (x0,x1)
	writeWord(x0);
	writeWord(x1);
	writeCmd(RASET);  // row address set (y0,y1)
	writeWord(y0);
	writeWord(y1);
}

void clearScreen(){
	setAddrWindow(0,0,XMAX,YMAX);  // set window to entire display
	writeCmd(RAMWR);
	unsigned int i;
	for (i=34322;i>0;--i){       // byte count = 128*160*2
		SPDR = 0;                // initiate transfer of 0x00
		while (!(SPSR & 0x80));  // wait for xfer to finish
	}
}

void hLine (uint8_t x0, uint8_t x1, uint8_t y, uint16_t color){  // draws a horizontal line in given color
	uint8_t width = x1-x0+1;
	setAddrWindow(x0,y,x1,y);
	write565(color,width);
}

void vLine (uint8_t x, uint8_t y0, uint8_t y1, uint16_t color){  // draws a vertical line in given color
	uint8_t height = y1-y0+1;
	setAddrWindow(x,y0,x,y1);
	write565(color,height);
}

void writeChar (const uint8_t ch, uint8_t x, uint8_t y, uint16_t color, uint16_t bgColor){  // write ch to display X,Y coordinates using ASCII 5x7 font
	uint16_t pixel;
	uint8_t row, col, bit, data, mask = 0x01;
	setAddrWindow(x,y,x+4,y+6);
	writeCmd(RAMWR);
	for (row=0; row<7;row++){      // iterate over 7 rows (up/down)
		for (col=0; col<5;col++){  // determining pixel color value for each of the 5 columns (left/right)
			data = pgm_read_byte(&(font5x7[ch-32][col]));  // font array is column major ordered thus each col iteration (0 to 5) 
			bit = data & mask;  // is a different column pixel in the same row
			if (bit==0) pixel=bgColor;
			else pixel=color;
			writeWord(pixel);
		}
	mask <<= 1;  // left shift one bit when moving to next row
	}
}

void writeString(const uint8_t *str, uint8_t x, uint8_t y, uint16_t color, uint16_t bgColor){
	for(; *str; str++){
		writeChar(*str, x, y, color, bgColor);
		x += 6;
	}
}