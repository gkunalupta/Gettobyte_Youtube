/*
 * Project1.cpp
 *
 * Created: 23-08-2020 21:18:01
 * Author : kunal
   0   0 0 0 0
   1   0 0 0 1
   2   0 0 1 0
   3   0 0 1 1
   4   0 1 0 0
   5   0 1 0 1
   6   0 1 1 0
   7   0 1 1 1
   8   1 0 0 0
   9   1 0 0 1
   A   1 0 1 0
   B   1 0 1 1
   C   1 1 0 0
   D   1 1 0 1
   E   1 1 1 0
   F   1 1 1 1

   X- IS ALPHAET TELLING WHICH PORT WE ARE USING
   N- IS PIN NUMBER OF THE PORT.
   e.g DDRB, DDRB2,PORTJ, PORTJ5.


   DDRX- CONFUGURES OUTPUT(1)/INPUT(0)
   PORTX - SET HIGH(1) OR LOW(0) STATE
   PINX - TELLS STATE OF THE PIN
   ox- hex(ff,0a,0b)
   ob- binary(1001010)
   
   7 6 5 4 3 2 1 0
   
   53 - PB0
   52- PB1
   51- PB2
   50- PB3
   10- pb4
   11- pb5
   12-pb6
   13-  pb7
   PJ0- 15 //switch 1
   PJ1-14  //switch 2
   MSB.....      LSB
 */ 

#include <avr/io.h>
#include <avr/delay.h>
//PB4 4
#define SW1 0
#define SW0 1

int main(void)
{
	DDRJ = 0b00000000;
	DDRB = 0xff;
	PORTB = (1<<PB4)|(1<<PB3);
	/*
	
	01-00000001<<1
	0001
	00010000 = (1<<PB4)
	01-00000001<<3
	00001000= (1<<PB3)
	00010000
   |00001000
    00011000    11100111
	PORTB= 00000000;
	      &11100111
		  000000000
		  
		  
		  PORTB = 11111111;
		         &11000000
		  
	|- OR
	& = ANd
    /* Replace with your application code */
    while (1) 
    {
		
		   // PINJ=                          00000000
	{
		PORTB &= ((1<<PB4)|(1<<PB3));
		_delay_ms(1000);
		PORTB &= ~(1<<PB4)|(1<<PB3);
		_delay_ms(1000);
	}
		
    }
}

