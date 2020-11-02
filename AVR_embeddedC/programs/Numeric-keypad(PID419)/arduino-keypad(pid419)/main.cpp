/*
 * arduino-keypad(pid419).cpp
 *
 * Created: 27-10-2020 13:05:28
 * Author : kunal
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "uarts.h"
#include "stdlib.h"
/*
R1 : PC0(37)
R2 : PC1(36)
R3 : PC2(35)
R4 : PC3(34)
C1 : PC4(33)
C2 : PC5(32)
C3 : PC6(31)
*/
#define R1 0
#define R2 1
#define R3 2
#define R4 3
#define C1 4
#define C2 5
#define C3 6

 uint8_t getkey()
 {
	  uint8_t keypressed=0;
	  
	  DDRC = 0b00001111;           // Column as input (PC6,PC5,PC4 th bit ) : set as 0(C3,C2,C1)
	                               // Row as output (PC3,PC2,PC1,PC0 th bit ) : set as 1(R4,R3,R2,R1)
	  _delay_ms(1);
	  PORTC = 0b11110000;          // Column pins:Input pins pull up resistor is activated by setting 1 to PORTC column pins
	                               //Row pins: Output pins are set to Low(0)
	  _delay_ms(1);
	  
	  
	  while(PINC == 0b11110000);    // If any button will be pressed then either of the PC6,PC5,PC4th bit (C3,C2,C1) will be made to 0 , hence
	                                // it will come out of while loop
	                                // if C1 is pressed : 11100000
	                                // if C2 is pressed : 11010000
	                                // if C3 is pressed : 10110000
	                                
									
	  keypressed = PINC;           //Stores the Value of which column is pressed in keypressed variable
	  
	  DDRC = 0b01110000;           //Columns as output(PC6,PC5,PC4 th bit): set as 1(C3,C2,C1)
	                               //Row as input(PC3,PC2,PC1,PC0 th bit) : set as 0(R4,R3,R2,R1)
	  _delay_ms(1);
	  PORTC = 0b10001111;          // Column pins:Output pins are set to Low(0)
	                              //Row pins: Input pins pull up resistor is activated by setting 1 to PORTC column pins
	  _delay_ms(1);
                                   //Now on setting Row as input and column as output : PINC will give 10001111 value(when no key is pressed)
                                   // if R1 is pressed --> 10001110
                                   // if R2 is pressed --> 10001101
                                   // if R3 is pressed --> 10001011
                                   // if R4 is pressed --> 10000111
	  
	  keypressed |= PINC;          // ORing the value of ROW and Column pressed when they are set as input respectively
	  
	 // bit0(keypressed);
	  printString0("\n");

	  switch (keypressed)
	  {
		 case(0b11101110):  //decimel0(1);               //C1:   11100000
		                                                 //R1: | 10001110
		                    //printString0(": ");
							return('1');
							break;
							 
		 case(0b11011110):  //decimel0(2);               //C2:   11010000
		                                                 //R1: | 10001110
		                    //printString0(": ");
		                    return('2');
		                    break;
		 
		 case(0b10111110):  //decimel0(3);               //C3:   10110000
		                    //printString0(": ");        //R1: | 10001110
		                    return('3');
							break;
							
		 case(0b11101101):  //decimel0(4);               //C1:   11100000
		                    //printString0(": ");        //R2: | 10001101
		                    return('4');
							break;
							
		 case(0b11011101):  //decimel0(5);               //C2:   11010000
		  		            //printString0(": ");        //R2: | 10001101
							 return('5'); 
							break;
							
		  case(0b10111101): //decimel0(6);              //C3:   10110000
		                    //printString0(": ");      //R2:  | 10001101
							return('6');
							break;
							
		  case(0b11101011):// decimel0(7);              //C1:   11100000
		                    //printString0(": ");       //R3: | 10001011
							return('7');
							break;
							
		  case(0b11011011): //decimel0(8);              //C2:   11010000
		                    //printString0(": ");       //R3: | 10001011
							return('8');
							break;
							
		  case(0b10111011): //decimel0(9);             //C3:   10110000
		                    //printString0(": ");      //R3: | 10001011
							return('9');
							break;
							
		  case(0b11100111):// UART_TxChar0('*');       //C1:   11100000
		                    //printString0(": ");      //R4: | 10000111
							return('*');
							break;
						
		  case(0b11010111): //decimel0(0);             //C2:   11010000
		                   // printString0(": ");      //R4: | 10000111
		                   return('0');
							break;
							
		  case(0b10110111):  //UART_TxChar0('#');       //C3:   10110000
		                     //printString0(": ");      //R4: | 10000111
							 return('#');
							 break;
							 
	  }
	 
	
     _delay_ms(100);
}

int main()
{
	UART_Init0();
	uint8_t a=0;
	
	while (1)
	{
		a = getkey();
		UART_TxChar0(a);
		
		
		/*
		for(int i=0;i<5;i++)
		{
		 num[i] = getkey();
		 UART_TxChar0(num[i]);
		 }
		 printString0(num);*/
	}
}
