#define SET_BIT(byte, bit) (byte |= (1 << bit))
#define CLEAR_BIT(byte,bit) (byte &= ~(1 << bit))
#define IS_SET(byte,bit) ((byte) & (1<<bit))

// Macro variables for equating MODE in pinMode()
#define OUTPUT 1
#define INPUT 0

//Macro Variables for equating State in digitalWrite()
#define HIGH 1
#define LOW 0
#include "GPIO.cpp"
