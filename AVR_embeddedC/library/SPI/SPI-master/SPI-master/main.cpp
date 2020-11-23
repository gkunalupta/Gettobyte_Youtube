/*
 * SPI-master.cpp
 *
 * Created: 11-11-2020 17:13:12
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
1) When configured as master,
   MOSI,SS,SCK are configured as OUTPUT and MISO as Slave
   a) MOSI: The data which is written on SPDR register is send in binary form via this pin
   b) SS: the desired SS pin is made LOW to select the corresponding Slave
   c) SCL: The Synchronized clock Pulses (High and Low Bits) are generated via this pin and fed to SCK pin of Slave
            SPR1:0 and SPI2 configure the frequency for SPI clock

2) by making SS pin LOW slave is selected and Data from shift register is shifted out.

3) If SS pin is configured as Input , it should be checked that it's line should not be 
made low by Peripheral Circuit , if it does then SPI system of MCU interprets that another master has 
made the SS pin low and will start acting like salve

4) When 3rd point is occurred , MSTR bit in SPCR register is cleared and
MOSI and SCK line automatically becomes input as MCU is configured as slave.

5) On completion of data transmission from MOSI line/MISO line SPIF flag is set , 
thus every time when SPIF is set 1 during Communication Session , MSTR bit should be checked and made 1
for re-enabling SPI master MODE

*/
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include "uarts.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define ACK 0x7E
#define LONG_TIME 10000


#define MISO PB3
#define MOSI PB2
#define SCK  PB1
#define SS   PB0

#define spi_data_direc DDRB
#define spi_port PORTB

#define spi_data_reg SPDR
#define spi_status_reg SPSR
#define spi_control_reg SPCR

//Initialize SPI Master Device
void spi_init_master (void)
{
	spi_data_direc = (1<<MOSI)|(1<<SCK)|(1<<SS);              //Set MOSI, SCK, SS as Output
	spi_control_reg = (1<<SPE)|(1<<MSTR)|(1<<SPR0); //Enable SPI, Set as Master
	                                     //Prescaler: Fosc/16, Enable Interrupts
}

//Function to send and receive data
uint8_t spi_tranceiver (uint8_t data)
{   

// Load data into the buffer
SPDR = data;

//Wait until transmission complete
while(!(SPSR & (1<<SPIF) ));

// Return received data
return(SPDR);
}

void spi_master_send(uint8_t data)                // --> done
{
	spi_port &= ~(1<<SS);
	spi_data_reg = data;                       //Load data into the buffer
	spi_port &= (1<<SS);
}

uint8_t spi_master_receive()                     //-->done
{
	//spi_port &= ~(1<<SS);
	SPDR = NULL;
	while(!(SPSR & (1<<SPIF) ));       //Wait until transmission complete
	return(SPDR);                      //Return received data
}

//Function to blink LED
void led_blink (uint8_t i)
{
	//Blink LED "i" number of times
	for (; i>0; --i)
	{
		PORTB|=(1<<0);
		_delay_ms(100);
		PORTB=(0<<0);
		_delay_ms(100);
	}
}

//Main
int main(void)
{   
	UART_Init0();
	spi_init_master();                     //Initialize SPI Master
	
	uint8_t data;                         //Received data stored here
	uint8_t x = 0;                      //Counter value which is sent
	
	while(1)
	{
		data = 0x00;                    //Reset ACK in "data"
		
// 		spi_master_send(++x);
// 				_delay_ms(500);                 //Wait
// 				printString0("Master sending:");
// 				decimel0(x);
// 				printString0("\n");
		
		data = spi_master_receive();
		_delay_ms(500);  
		        printString0("Master receiving ");
		        decimel0(data);
		        printString0("\n");
		
	}
}