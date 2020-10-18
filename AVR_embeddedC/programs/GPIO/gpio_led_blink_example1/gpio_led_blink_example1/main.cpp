/*
 * GccApplication1.cpp
 *
 * Created: 9/7/2019 10:41:34 PM
 * Author : kunal
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <uarts.h>
int main(void)
{  UART_Init0();
	//Set PORTB1 as output
	DDRB=0b00000010;

	while(1)
	{
		//Set PB1=High(+5v), this will turn on the LED
		PORTB=0b00000010;
		_delay_ms(5000); // wait for half second, then turn it off

		//Set PB1=Low(GND)
		PORTB=0b11111101;
		_delay_ms(500);
	}
}


