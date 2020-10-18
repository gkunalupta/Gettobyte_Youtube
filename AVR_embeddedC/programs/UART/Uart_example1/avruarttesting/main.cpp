/*
 * avruarttesting.cpp
 *
 * Created: 10-07-2020 22:51:10
 * Author : kunal
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
void UART_Init0();
char UART_RxChar0();
void UART_TxChar0(unsigned short data);//unsigned short(0-65535)
void printString0( const char myString[] );
char rxstring0(char *buff);
void uart_num0(unsigned short num);
void bit0(unsigned short val);//unsigned short (0-65535)
void decimel0(unsigned short val);
void UART_Init0()
{   //103 fpr 9600
	//8 for 115200
	UBRR0 = 51;
	UCSR0B = (1<<TXEN0)|(1<<RXEN0);
	UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);
	//UCSR0A=(1<<U2X0);
}

void UART_TxChar0(unsigned short data)
{
	while((UCSR0A & (1<<UDRE0))==0);
	UDR0 = data;
	
}


char UART_RxChar0()
{   //unsigned char status, resh, resl;
	//status = UCSR0A;
	
	// 	printString0("value of uscra before \n ");
	// 	bit0(UCSR0A);
	// 	printString0("\n");
	while(!(UCSR0A & (1<<RXC0)));
	//     printString0(" \nvalue of ucsra after \n");
	// 	bit0(UCSR0A);	// 	printString0("\n");
	// 	UDR0=pop;
	// 	    printString0("\n");
	return UDR0;
}

//stores the incoming string to buff
char rxstring0(char *buff)
{  int i=0;
	char myValue;
	do
	{
		// printString0("do \n");

		myValue = UART_RxChar0();
		if(myValue!='\n')
		{
			buff[i]=myValue;
			UART_TxChar0(buff[i]);
			i++;
		}    else
		{
			buff[i]='\0';
			break;
		}
		// 	printString0("5\n");
		// 	printString0("value of uscra on \n ");
		// 	bit0(UCSR0A);
	}
	while( !(UCSR0A & (1<<RXC0)));

	printString0(buff);
	return myValue;
}

void printString0( const char *myString)      /////to print any string
{

	while (*myString)
	{
		UART_TxChar0(*myString++);
	}
}


void uart_num0(unsigned short num)
{
	unsigned char H=0,T=0,O=0;
	H=num/100;
	T=(num - (H*100))/10;
	O=(num - (H*100) - (T*10));
	
	UART_TxChar0(H+48);
	UART_TxChar0(T+48);
	UART_TxChar0(O+48);
	UART_TxChar0(num);
}

void bit0(unsigned short val)
{
	int  ptr;
	for(ptr=7;ptr>=0;ptr--)
	{
		if ((val & (1<<ptr))==0)
		{
			UART_TxChar0('0');
		}
		else
		{
			UART_TxChar0('1');
		}
	}
}
// Transmit an unsigned 16 bit value as up to five decimal characters
void decimel0(unsigned short val)
{
	unsigned char buf[5];
	int ptr;
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
	printString0("kunal");
	while (1)
	{
	}}
