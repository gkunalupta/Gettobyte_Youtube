/*
 * kunal serial2.cpp
 *
 * Created: 11/16/2019 12:05:28 AM
 * Author : kunal
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

void UART_Init();
char UART_RxChar();
void UART_TxChar(const char data);
//DDRB=0xff;
int main(void)
{DDRB=0xff;
	char myValue;
	
	UART_Init();
	
	while (1)
	{   //PORTB=0xff;
		UART_TxChar('k');
		myValue = UART_RxChar();
		UART_TxChar(myValue);
		
	}
}

void UART_Init()
{
	UBRR0L = 103;
	UCSR0B = (1<<TXEN0)|(1<<RXEN0);
	UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);
}

void UART_TxChar(char data)
{//PORTB=0xff;
	while(!(UCSR0A & (1<<UDRE0)));
	{
		UDR0 = data;
//PORTB=0x00;
	}
}

char UART_RxChar()
{//PORTB=0xff;
	while(!(UCSR0A & (1<<RXC0)));
	{
		PORTB=0xff;
		return UDR0;

}PORTB=0x00;

}