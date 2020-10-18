/*
 * GccApplication1.cpp
 *
 * Created: 9/7/2019 10:41:34 PM
 * Author : kunal
 */ 
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	//Set PORTB1 as output
	DDRB=0b11111111;
	DDRC=0xFF;
int i,j,k ,l;
	while(1)
	{
		if(PINC==Ox01)
	   { 
		   i=0;
		   i++
		
		PORTB=0b00000001;
		
		}
		if(PINC==Ox02)
		{j=0;
			j++;
			PORTB=0b00000001;
		}
		
		if(PINC==Ox03)
		{
			PORTB=0b00000001;
		}
		if(PINC==Ox04)
		{
			PORTB=0b00000001;
		
	}
}


