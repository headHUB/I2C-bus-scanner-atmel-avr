#define F_CPU 16000000UL     // CPU clocked at 16MHz
#define SCL_CLOCK  100000UL  // I2C bus clocked at 100kHz
#include <stdio.h>           // snprintf()
#include <util/delay.h>      // _delay_ms()
#include "I2C.h"             // multi-master, multi-slave, packet switched, single-ended, serial bus
#include "ST7735.h"          // TFT-LCD controller|driver

int main(){
	// Configure All Pins as Inputs
	DDRB = 0x00;  //0 == Input; 1 = Output
	DDRC = 0x00;
	DDRD = 0x00;
	// Enable All Pull-Ups
	PORTB = 0xFF;  //0 = Tri-State; 1 = Pull-Up
	PORTC = 0xFF;
	PORTD = 0xFF;

	// TFT LCD Pin Configuration
	DDRB  |= (1<<DDB5) | (1<<DDB3) | (1<<DDB2) | (1<<DDB1) | (1<<DDB0);  // set B0-B3, B5 as outputs
	PORTB |= (1<<PORTB0);                                                // start with TFT reset line inactive high

	// SPI Configuration
	SPCR |= (1<<SPE) | (1<<MSTR);  // SPI enabled as master, Mode0 at 4 MHz
	SPSR |= (1<<SPI2X);            // double the SPI rate: 4-->8 MHz

	// Reset TFT LCD Display
	PORTB &= ~(1<<PORTB0);  // pull ST7735 reset line low (PB0)
	_delay_us(100);         // ST7735 datasheet specifies minimum of 10us and no maximum. 80us or less fails to initiate reset. Use 100us.  
	PORTB |= (1<<PORTB0);   // return reset line high
	_delay_ms(125);         // ST7735 datasheet specifies maximum of 120ms and no minimum. Wait 125mS for reset process to complete

	// Initialize TFT LCD Display
	writeCmd(SLPOUT);     // take display out of sleep mode which is the default after applying power
	_delay_ms(125);       // ST7735 datasheet specifies maximum of 120ms and no minimum. Wait 125mS for TFT driver circuits to stabalize
	writeCmd(COLMOD);     // select Interface Pixel Format register (COLMOD)
	writeByte(0x05);      // set Pixel Color Format (Color Depth) to 16-bit/pixel: RGB=(565)
	writeCmd(DISPON);     // turn the display on
	setOrientation(180);  // orient per best viewing angle

	// Initialize I2C Bus
	TWSR &= ~(1<<TWPS1) & ~(1<<TWPS0);  // set TWI bit rate prescaler value to 1-one
	TWBR = ((F_CPU/SCL_CLOCK)-16)/2;    // SCL frequency = CPU Clock Frequency / (16+(2*TWBR*Prescaler))


	uint8_t i, xPos, yPos, asciiText[3];

	while(1){

		clearScreen();              // erase previous screen
		vLine(2, 0, 131, White);    // draw vertical line to define screen left edge
		vLine(129, 0, 131, White);  //                                     right edge
		hLine(0, 131, 3, White);    // draw horizontal line to define screen top edge
		hLine(0, 131, 130, White);  //                                       bottom edge

		writeString("I2C Bus Scanner", 8, 8, Blue429, Black);  // write static text to LCD
		writeString("Scanning", 8, 32, White, Black);
		writeString("Address  0x", 8, 44, White, Black);
		writeString("Slave Address(s)", 8, 68, White, Black);

		yPos = 80;  // set cursor to pixel position (0,80)
		xPos = 0;

		for (i = 8; i < 120; i++){                  // iterate over valid 7-bit address range
			if(!i2cStart((i << 1) | 0)){            // if i2cStart() returns 0, then no response
				snprintf(asciiText, 3, "%02X", i);  // convert hex address scanned to ascii
				writeString(asciiText, 75, 44, White, Black);  // write the address scanned to LCD at pixel location (75,44)
			}
			else{                // else i2cStart() returns 1, slave ACK received
				xPos += 25;      // move cursor 25 pixels right to avoid overwriting the last address
				if(xPos > 100){  // if cursor is farther right than 100 pixels
					xPos = 25;   // reset cursor back to pixel 25 on the x-axis
					yPos += 12;  // move cursor down 12 pixels on the y-axis i.e. next line
				}
				snprintf(asciiText, 3, "%02X", i);                   // convert hex address of slave to ascii
				writeString(asciiText, xPos, yPos, Blue429, Black);  // write slave address to LCD at pixe location (xPos,yPos)
			}

			i2cStop();      // release the bus
			_delay_ms(50);  // pause for LCD screen readability when cycling through addresses being scanned
		}
		_delay_ms(300000);  // wait 5 minutes before rescanning
	}
}