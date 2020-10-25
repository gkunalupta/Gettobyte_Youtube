/*
 * UART-interrupts.cpp
 *
 * Created: 25-10-2020 23:06:19
 * Author : kunal
 */ 

#include <avr/io.h>
#include "uarts.h"
 
 // USART Receiver buffer
 #define RX_BUFFER_SIZE_UART0 255
 uint8_t Rx_Buffer_UART0[RX_BUFFER_SIZE_UART0]; // character array (buffer)
 uint8_t RX_Wr_Index_UART0; //index of next char to be put into the buffer  // head
 uint8_t RX_Rd_Index_UART0; //index of next char to be fetched from the buffer    //tail
 uint8_t RX_Counter_UART0; //a total count of characters in the buffer
 bool RX_Buffer_Overflow_UART0; // This flag is set on USART Receiver
uint32_t RX_No_of_byte_UART0=0;

char RX_DATA_UART0[RX_BUFFER_SIZE_UART0];
 char rx_byte;
ISR(USART0_RX_vect)
{
 
 // We only ever get here when an RXC interrupt has occurred;
 // Therefore, we know that there must be at least 1 byte in UDR

 // get the 1st byte
 rx_byte = UDR0;
 Rx_Buffer_UART0[RX_Wr_Index_UART0]= rx_byte;   /* put received char in buffer from head pointer */
 if(++RX_Wr_Index_UART0 > RX_BUFFER_SIZE_UART0)
 RX_Wr_Index_UART0 = 0;
 if(++RX_Counter_UART0 > RX_BUFFER_SIZE_UART0) /* keep a character count */
 { /* overflow check.. */
	 RX_Counter_UART0 = RX_BUFFER_SIZE_UART0; /* if too many chars came */
	 RX_Buffer_Overflow_UART0 = 1; /* in before they could be used */
	 } /* that could cause an error!! */
 RX_No_of_byte_UART0=RX_Counter_UART0 ;
//(Rx_Buffer_UART0);
//decimel0(RX_No_of_byte_UART0);
}
char getchar_UART0()
{
	char c;
	c = Rx_Buffer_UART0[RX_Rd_Index_UART0]; /* get one from the buffer..*/
	if(++RX_Rd_Index_UART0 > RX_BUFFER_SIZE_UART0) /* wrap the pointer */
	RX_Rd_Index_UART0 = 0;
	if(RX_No_of_byte_UART0)
	RX_No_of_byte_UART0--; /* keep a count (buffer size) */
	return c;
	
}
void getstring_UART0()
{
	//printString0(" Number of characters received : ");
	//decimel0(RX_No_of_byte_UART0);
	//printString0("\n");
	uint8_t x=0;
	memset(RX_DATA_UART0, '\0',RX_BUFFER_SIZE_UART0);
	decimel0(RX_No_of_byte_UART0);
	while (!RX_No_of_byte_UART0);
	{
		RX_DATA_UART0[x]= getchar_UART0();
		x++;
		printString0(RX_DATA_UART0);
	}
	//printString0(RX_DATA_UART0);
	//_delay_ms(1000);
	
}
int main(void)
{
	UART_Init0();
	printString0("kunal\n");
	sei();
	
    /* Replace with your application code */
    while (1) 
    {
	    
		    getstring_UART0();
	    
	
    }
}

