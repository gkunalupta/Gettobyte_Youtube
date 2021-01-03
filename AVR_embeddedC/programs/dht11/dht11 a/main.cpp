/*
 * dht11 a.cpp
 *
 * Created: 3/22/2020 9:44:16 PM
 * Author : kunal
 // DDR-output/input
 // PORT-high/low
 // PIN-check
 //PB4
 //Fcpu=16000000
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include "dht11.h"

#define test true

int main(void)
{  
	 UART_Init0();
	uint8_t x[5];
	
    while (1) 
    {
		
			dht11_init();
			dht11_find_response();
			dht11_receivedht(x);
			printString0("\nHumidity of dht11 ");
			
			decimel0(x[0]);
			printString0(".");
			decimel0(x[1]);
			
			printString0("\nTemperature of dht11 ");
			
			decimel0(x[2]);
			printString0(".");
			decimel0(x[3]);
			
			_delay_ms(2000);
			printString0("\n");
			
			
// 			y[0]=0; y[1]=0,y[2]=0,y[3]=0,y[4]=0;
// 			dht11_init10();
// 			dht11_find_response10();
// 			dht11_receivedht10(y);
// 			printString0("\nHumidity of dht11 10 ");
// 			decimel0(y[0]);
// 			printString0(".");
// 			decimel0(y[1]);
// 			printString0("\nTemperature of dht11 10 ");
// 			decimel0(y[2]);
// 			printString0(".");
// 			decimel0(y[3]);
// 			_delay_ms(2000);
// 			printString0("\n");
		
}
}
