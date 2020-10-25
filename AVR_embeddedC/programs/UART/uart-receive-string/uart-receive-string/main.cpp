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
	char abc[20];
	
    /* Replace with your application code */
    while (1) 
    {
		rxstring0(abc);
		printString0(abc);
    }
}

