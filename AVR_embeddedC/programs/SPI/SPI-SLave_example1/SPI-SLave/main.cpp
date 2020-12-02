/*
 * SPI-SLave.cpp
 *
 * Created: 11-11-2020 17:17:47
 * Author : kunal
 */ 
/* 
MISO -50(PB3)  --> Master In SLave out: Master Receives data from salve via this line
MOSI -51(PB2)  --> Moster Out Slave In: Master Sends data to Slave Via this line
SCK  -52(PB1)  --> Synchronous Clock: From this line clock is generated
SS   -53(PB0)  --> Slave Select: Slave is selected from this line by making the desired 
                   SS pin Low.
*/

/*
When Configured as Slave
1) MOSI,SCK,SS Are selected as input pins as these pins will be drived from the master SPI pins
2) MISO is selected as output when data has to be send from slave to master

*/

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uarts.h"

#define ACK 0x7E

#define MISO PB3
#define MOSI PB2
#define SCK  PB1
#define SS   PB0

#define spi_data_direc DDRB
#define spi_port PORTB

#define spi_data_reg SPDR
#define spi_status_reg SPSR
#define spi_control_reg SPCR

void spi_init_slave (void)
{
	                      spi_data_direc=(1<<MISO);   //MISO as OUTPUT       
       spi_control_reg=(1<<SPE);      //Enable SPI
}

//Function to send and receive data
unsigned char spi_tranceiver (unsigned char data)
{

// Load data into the buffer
SPDR = data;

//Wait until transmission complete
while(!(SPSR & (1<<SPIF) ));

// Return received data
return(SPDR);                               //Return received data
}

void spi_slave_send(uint8_t data)           //-->done
{
	spi_data_direc=(1<<MISO);   //MISO as OUTPUT
	spi_data_reg = data;
	spi_port &= ~(1<<SS);
}

uint8_t spi_slave_receive()                  //--> done
{
	while(!(SPSR & (1<<SPIF) ));                  //Wait until transmission complete
	return(SPDR);                                 //Return received data
}


int main(void)
{     
	UART_Init0();
	spi_init_slave();                             //Initialize slave SPI
	uint8_t data;   
    uint8_t x = 100;
	while(1)
	{
	data = 0x00;  
	
	spi_slave_send(++x);
		_delay_ms(500);                
		printString0("slave sending:");
		decimel0(x);
		printString0("\n");	


// 	data = spi_slave_receive();
// 	     _delay_ms(500);                 //Wait
// 	     printString0("Slave receiving ");
// 	     decimel0(data);
// 	     printString0("\n");
	}
}