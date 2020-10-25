/*
 * UART-interrupts.cpp
 *
 * Created: 25-10-2020 23:06:19
 * Author : kunal
 */ 

#include <avr/io.h>
#include "uarts.h"
char rx_byte;
ISR(USART0_RX_vect)
{


	// We only ever get here when an RXC interrupt has occurred;
	// Therefore, we know that there must be at least 1 byte in UDR

	// get the 1st byte
	rx_byte = UDR0;
    UART_TxChar0(rx_byte);


}

int main(void)
{
	UART_Init0();
	printString0("kunal\n");
	sei();
    /* Replace with your application code */
    while (1) 
    {
    }
}

