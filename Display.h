#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "Arduino.h"
/*--------------------------------------------------------------------------------------------------------------*/
#ifndef Display_h
#define Display_h
/*--------------------------------------------------------------------------------------------------------------*/
//Port D
#define DB4       4
#define DB5       5
#define DB6       6
#define DB7       7
 
//Port B
#define T_BASE 8 //Transistor base pin
#define E   11
#define RS  12

//macros for Print_To_LCD function
#define DEC 10
#define HEX 16

//instruction macros
#define CLEAR_SCREEN          0x01
#define RETURN_HOME           0x02
#define ENTRY_MODE_SET        0x04
#define DISPLAY_CONTROL       0x08
#define CURSOR_SHIFT          0x10
#define FUNCTION_SET          0x20
#define SET_CGRAM_ADDR        0x40
#define SET_DDRAM_ADDR        0x80

// flags for display entry mode
#define ENTRY_RIGHT           0x00
#define ENTRY_LEFT            0x02
#define ENTRY_SHIFT_INCREMENT 0x01
#define ENTRY_SHIFT_DECREMENT 0x00

// flags for display on/off control
#define DISPLAY_ON            0x04
#define DISPLAY_OFF           0x00
#define CURSOR_ON             0x02
#define CURSOR_OFF            0x00
#define BLINK_ON              0x01
#define BLINK_OFF             0x00

// flags for display/cursor shift
#define DISPLAY_MOVE          0x08
#define CURSOR_MOVE           0x00
#define MOVE_RIGHT            0x04
#define MOVE_LEFT             0x00

// flags for function set
#define _8BIT_MODE            0x10
#define _4BIT_MODE            0x00
#define _2_LINE               0x08
#define _1_LINE               0x00
#define _5x10_DOTS            0x04
#define _5x8_DOTS             0x00
/*--------------------------------------------------------------------------------------------------------------*/
//print data to screen
void Print_Data(uint8_t data);

//print command to lcd
void Print_CMD(uint8_t cmd);

//Setup Display
void LCD_Setup();

//set custom character to CGRAM
void Set_CGRAM(uint8_t* Char_Arr);

//print some data (string,number etc.) to lcd
void Print_To_LCD(char* str);
void Print_To_LCD(const char* str);
void Print_To_LCD(int32_t num, uint8_t base = DEC);
/*--------------------------------------------------------------------------------------------------------------*/
#endif
