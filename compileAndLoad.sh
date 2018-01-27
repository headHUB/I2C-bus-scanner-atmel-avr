# install avr compiler (gcc-avr), avr libraries (avr-libc), and programming utility (avrdude) 
# $apt-get install gcc-avr avr-libc avrdude

avr-gcc -g -Os -mmcu=atmega328p -c main.c;
avr-gcc -g -mmcu=atmega328p -o main.elf main.o;
avr-objcopy -j .text -j .data -O ihex main.elf main.hex;
avrdude -c avrispmkII -p ATmega328p -U flash:w:main.hex -v;