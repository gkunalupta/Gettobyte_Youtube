/*
 * uart-receive-string.cpp
 *
 * Created: 25-10-2020 23:11:00
 * Author : kunal
 */ 

#include <avr/io.h>
#include "uarts.h"

int main(void)
{
	UART_Init0();
	UART_Init1();
	char abc[200];
	printString1("AT+GMR\r\n");
			rxstring1(abc);
			printString0(abc);
    /* Replace with your application code */
    while (1) 
    {
		
		//rxstring1(abc);
		//printString0(abc);
    }
}

