/*
 * rtc3231.cpp
 *
 * Created: 4/13/2020 4:57:40 PM
 * Author : kunal
 */ 

#include <avr/io.h>
#include "i2c master.h"
//#include "uarts.h"
// Convert normal decimal numbers to binary coded decimal
uint8_t decimalToBcd(uint8_t val){
	return( (val/10*16) + (val%10) );
}

// Convert binary coded decimal to normal decimal numbers
uint8_t bcdToDec(uint8_t val){
	return( (val/16*10) + (val%16) );
}
#define RTC_WADDR 0b11010000   //Slave Write
#define RTC_RADDR 0b11010001   //Slave Read

#define Status_reg 0x0F
#define Control_reg 0x0E
#define Date_reg 0x03
#define Time_reg 0x00
#define Alarm1_reg 0x07
#define Alarm2_reg 0x0B
#define Temp_reg 0x11

#define Enable_32khz_output 0b00001000    // byte to be send in status register for enabling 32K square wave
#define disable_32khz_output 0b00000000   //byte to be send in status register for disabling 32K square wave
struct rtc_time
{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
};
struct rtc_date
{
	uint8_t wday;
	uint8_t day;
	uint8_t month;
	uint8_t year;
};
struct alarm1
{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t wday;
	uint8_t day;
};
struct alarm2
{
    uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t wday;
	uint8_t day;
};
void rtc3231_32khz_output()
{
	TWI_start();
	TWI_write_slave_address(RTC_WADDR);  // Slave address with Write mode
	TWI_write_data(Status_reg);   // Address of Status Register of RTC3231
	TWI_write_data(0b00000000);  //Data for Status register of RTC3231
	TWI_stop();
}
void rtc3231_init(void)
{    
	printString0("Initialize \n");
	TWI_init_master();
	printString0("start  \n");
	TWI_start();
    printString0("write address \n");
	TWI_write_slave_address(RTC_WADDR);
    printString0(" address of control register \n");
	TWI_write_data(Control_reg);
    printString0(" data for control register \n");
	TWI_write_data(0b00101000);     //convert Temp, No alarm interrupt on INT pin
    printString0("data for status register \n");
	TWI_write_data(0x00001000);     //Enable 32K square signal
    printString0("stop \n");
	TWI_stop();
	printString0("Rtc initialized \n"); 
}
void rtc3231_read_time(struct rtc_time *time)
{
	TWI_start();
	TWI_read_slave_address(RTC_RADDR);
	time->sec = bcdToDec(TWI_read_dataAck());
	time->min = bcdToDec(TWI_read_dataAck());
	time->hour =bcdToDec(TWI_read_dataNack());
	TWI_stop();
}
void rtc3231_read_date(struct rtc_date *date)
{    
	TWI_start();
	TWI_write_slave_address(RTC_WADDR);
	TWI_write_data(Date_reg);
	TWI_stop();
	
	TWI_start();
	TWI_read_slave_address(RTC_RADDR);
	date->wday = bcdToDec(TWI_read_dataAck());
	date->day = bcdToDec(TWI_read_dataAck());
	date->month = bcdToDec(TWI_read_dataAck());
	date->year = bcdToDec(TWI_read_dataNack());
	TWI_stop();

}
void rtc3231_read_datetime(struct rtc_time *time, struct rtc_date *date)
{    
	TWI_start();
	TWI_read_slave_address(RTC_RADDR);
	time->sec = bcdToDec(TWI_read_dataAck());
	time->min = bcdToDec(TWI_read_dataAck());
	time->hour = bcdToDec(TWI_read_dataAck());
	date->wday = bcdToDec(TWI_read_dataAck());
	date->day = bcdToDec(TWI_read_dataAck());
	date->month = bcdToDec(TWI_read_dataAck());
	date->year = bcdToDec(TWI_read_dataNack());
    TWI_stop();
}
void dispalytimedate(struct rtc_time *time, struct rtc_date *date)
{
	decimel0(date->day);
	printString0("/");
    decimel0(date->month);
	printString0("/");
	decimel0(date->year);
	printString0("   , ");
	decimel0(date->wday);
	printString0("   , ");
	decimel0(time->hour);
	printString0(":");
	decimel0(time->min);
	printString0(":");
	decimel0(time->sec);
    printString0("\n");
	
}
void displaydate (struct rtc_date *date)
{
	decimel0(date->day);
	printString0("/");
	decimel0(date->month);
	printString0("/");
	decimel0(date->year);
	printString0("   , ");
	decimel0(date->wday);
	printString0("   , ");
}
void rtc3231_write_time(struct rtc_time *time)
{
	TWI_start();
	TWI_write_slave_address(RTC_WADDR);
	TWI_write_data(Time_reg);
	TWI_write_data(time->sec);
	TWI_write_data(time->min);
	TWI_write_data(time->hour);
	TWI_stop();
}
void rtc3231_write_date(struct rtc_date *date)
{
	TWI_start();
	TWI_write_slave_address(RTC_WADDR);
	TWI_write_data(Date_reg);
	TWI_write_data(date->wday);
	TWI_write_data(date->day);
	TWI_write_data(date->month);
	TWI_write_data(date->year);
	TWI_stop();
}
void set_alarm1(struct alarm1 *AL1)
{
TWI_start();
TWI_write_slave_address(RTC_WADDR);
TWI_write_data(Alarm1_reg);
TWI_write_data(AL1->sec);
TWI_write_data(AL1->min);
TWI_write_data(AL1->hour);
TWI_write_data(AL1->wday);
TWI_write_data(AL1->day);
TWI_stop();	
}
void setdatetime(struct rtc_time *rt, struct rtc_date *rd)
{
	rt->sec=00;
	rt->min=0x37;
	rt->hour=0x23;
	rd->wday=07;
	rd->day=0x03;
	rd->month=0x01;
	rd->year=0x21;
	rtc3231_write_date(rd);
	rtc3231_write_time(rt);
}
uint8_t DS3231_getTemperature(void)
{
	
	uint8_t msb;
	uint8_t lsb;
    TWI_start();
    TWI_write_slave_address(RTC_WADDR);
    TWI_write_data(Temp_reg);
    TWI_stop();

    TWI_start();
    TWI_read_slave_address(RTC_RADDR);
    msb= TWI_read_dataAck();
    lsb=TWI_read_dataNack();
	TWI_stop();
	
	return (float)msb + ((lsb >> 6) * 0.25f);
}

int main(void)
{   
	
		
	UART_Init0();
	rtc3231_init();
	printString0("***********rtcds3231********************");
	float a;
	rtc_time rt;
	rtc_date rd;
	setdatetime(&rt,&rd);
	
	//rtc3231_32khz_output();
	    /* Replace with your application code */
    while (1) 
    {    
		  printString0("Temperature : ");
		  a=DS3231_getTemperature();
	      decimel0(a);
		  printString0("\n");
		  
// 		  rtc3231_read_date(&rd);
// 		 displaydate((&rd));
		  
		  rtc3231_read_datetime(&rt,&rd);
		  dispalytimedate(&rt,&rd);
		  
		  printString0("\n");
		  _delay_ms(1000);
	}
}

