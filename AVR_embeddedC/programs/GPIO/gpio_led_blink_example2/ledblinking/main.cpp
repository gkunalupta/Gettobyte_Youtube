/*
 * ledblinking.cpp
 *
 * Created: 23-08-2020 21:14:33
 * Author : kunal
   0   0 0 0 0
   1   0 0 0 1
   2   0 0 1 0
   3   0 0 1 1
   4   0 1 0 0
   5   0 1 0 1
   6   0 1 1 0
   7   0 1 1 1
   8   1 0 0 0
   9   1 0 0 1
   A   1 0 1 0
   B   1 0 1 1
   C   1 1 0 0
   D   1 1 0 1
   E   1 1 1 0
   F   1 1 1 1

   X- IS ALPHAET TELLING WHICH PORT WE ARE USING
   N- IS PIN NUMBER OF THE PORT.
   e.g DDRB, DDRB2,PORTJ, PORTJ5.


   DDRX- CONFUGURES OUTPUT(1)/INPUT(0)
   PORTX - SET HIGH(1) OR LOW(0) STATE
   PINX - TELLS STATE OF THE PIN
   ox- hex(ff,0a,0b)
   ob- binary(1001010)
   7 6 5 4 3 2 1 0
   MSB.....      LSB

PH3-6-SW1
PB4-10-LED1

*/
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/delay.h>
#include "uarts.h"
#include "GPIO.h"


#define SW1 PH3 //Switch1 connected to PH3: 6 digital pin
#define LED1 PB4  //LED1 connected to PB4: 10 digital pin

void myname()
{
	printString0("Kunal Gupta\n");
}

void channel_name()
{
	printString0("Gettobyte\n");
}



int main(void)
{ UART_Init0();
	char buff[100];
	//PORTB
    while (1) 
	{
		myname();
		//MyMethod();

		_delay_ms(1000);
		channel_name();
		
		_delay_ms(1000);
			printString0("1\n");
			_delay_ms(1000);
			printString0("2\n");
			_delay_ms(1000);
		
	}

}

















/* 

#define SW1 PH3 //Switch1 connected to PH3: 6 digital pin
#define LED1 PB4  //LED1 connected to PB4: 10 digital pin


// For buzzer alarm using Capacitive sensor
#define buzzer PJ1    // buzzer connected to 14 digital pin
#define cap_sensor PJ0  // cap_sensor connected tp 15 digital pin


//For Relay ON/OFF using Capacitive Touch Sensor
#define relay PE5      // relay connected to 3 digital pin
#define cap_touch PE4    //capacitive touch switch connected tp 2 digital pin




UART_Init0();
pinMode(buzzer,&DDRJ, OUTPUT);
pinMode(relay,&DDRE, OUTPUT);
pinMode(LED1,&DDRB, OUTPUT);

pinMode(cap_sensor, &DDRJ,INPUT);
pinMode(cap_touch, &DDRE,INPUT);
pinMode(SW1,&DDRH,INPUT);

while (1)

{
	
	
	if(digitalRead(cap_sensor,&PINJ))
	digitalWrite(buzzer,&PORTJ,HIGH);
	else
	digitalWrite(buzzer,&PORTJ,LOW);
	
	
	
	if(digitalRead(SW1,&PINH))
	digitalWrite(LED1,&PORTB,HIGH);
	else
	digitalWrite(LED1,&PORTB,LOW);
	
	
	if(digitalRead(cap_touch,&DDRE))
	digitalWrite(relay,&DDRE,HIGH);
	else
	digitalWrite(relay,&DDRE,LOW);
	
	
}
}*/