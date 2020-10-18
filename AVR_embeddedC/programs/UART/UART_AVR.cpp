/*
 * Uart_AVR.cpp
 *
 * Created: 23-09-2020 20:47:19
 * Author : kunal
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <GPIO.h>

#define uart0_ucsrA UCSR0A
#define uart0_ucsrB UCSR0B
#define uart0_ucsrC UCSR0C
#define uart0_UDR UDR0
#define uart0_baudrate UBRR0

void UART_Init0()
{    //103 fpr 9600
	//8 for 115200
	uart0_baudrate = 103;
	uart0_ucsrB = (1<<TXEN0)|(1<<RXEN0); //00001000, 00010000
	
}

void UART_TxChar0(uint16_t data)
{
	while((uart0_ucsrA & (1<<UDRE0))==0); //00100000
	uart0_UDR = data;
	
}


char UART_RxChar0()
{
	while(!(uart0_ucsrA & (1<<RXC0)));
	return uart0_UDR;
}

//stores the incoming string to buff
void rxstring0(char *buff)
{  int i=0;
	char myValue;
	do
	{

		myValue = UART_RxChar0();
		if(myValue!='\n')
		{
			buff[i]=myValue;
			i++;
		}    else
		{
			buff[i]='\0';
			break;
		}

	}
	while( !(uart0_ucsrA & (1<<RXC0)));


}

void printString0( const char *myString)      /////to print any string
{

	while (*myString)
	{
		UART_TxChar0(*myString++);
	}
}




//Transmit an unsigned 32 bit value as upto 8 bits in binary form
void bit0(uint32_t val)
{
	int8_t ptr;
	for(ptr=7;ptr>=0;ptr--)
	{
		if ((val & (1<<ptr))==0) //100000000, 01000000,
		{
			UART_TxChar0('0');
		}
		else
		{
			UART_TxChar0('1');
		}
	}
}
// Transmit an unsigned 32 bit value as up to five decimal characters
void decimel0(uint32_t val)
{
	unsigned char buf[5];
	int8_t ptr;
	for(ptr=0;ptr<5;++ptr) {
		buf[ptr] = (val % 10) + '0';
		val /= 10;
	}
	for(ptr=4;ptr>0;--ptr) {
		if (buf[ptr] != '0') break;
	}
	for(;ptr>=0;--ptr) {
		UART_TxChar0(buf[ptr]);
	}
}


int main(void)
{
	UART_Init0();
	char rec [100];
	int a =23;
	printString0("************GETTOBYTE*********** \n");
    /* Replace with your application code */
    while (1) 
    {
		decimel0(a);
		bit0(a);
		printString0("Write a string \n ");
		rxstring0(rec);   
		printString0("\n received String \n");
		printString0(rec);
		 }
}

