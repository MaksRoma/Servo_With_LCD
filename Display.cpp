#include <stdint.h>
#include "Arduino.h"
#include "Display.h"
/*--------------------------------------------------------------------------------------------------------------*/
void Print_DBus(uint8_t num)
{
  digitalWrite(DB4,(num & 0x1) >> 0);
  digitalWrite(DB5,(num & 0x2) >> 1);
  digitalWrite(DB6,(num & 0x4) >> 2);
  digitalWrite(DB7,(num & 0x8) >> 3);
  //latching
  delayMicroseconds(500);
  digitalWrite(E,HIGH);
  delayMicroseconds(500);
  digitalWrite(E,LOW);
  delayMicroseconds(500);
}
/*--------------------------------------------------------------------------------------------------------------*/
void Print_Data(uint8_t data)
{
  digitalWrite(RS, HIGH);
  //print MSB 4 bits
  Print_DBus((data & 0xF0) >> 4);
  //print LSB 4 bits
  Print_DBus(data & 0x0F);
}
/*--------------------------------------------------------------------------------------------------------------*/
void Print_CMD(uint8_t cmd)
{
  digitalWrite(RS, LOW);
  //print MSB 4 bits
  Print_DBus((cmd & 0xF0) >> 4);
  //print LSB 4 bits
  Print_DBus(cmd & 0x0F);
}
/*--------------------------------------------------------------------------------------------------------------*/
void LCD_Setup()
{
  delay(100);

  digitalWrite(RS, LOW);

  //Sets to 4-bit operation. otherwise, next instructions will be wrong execute
  Print_DBus(0x3);
  delay(5);
  Print_DBus(0x3);
  delayMicroseconds(100);
  Print_DBus(0x3);
  delayMicroseconds(100);

  Print_DBus(0x2);
  delayMicroseconds(100);
  Print_CMD(FUNCTION_SET | _4BIT_MODE | _2_LINE | _5x8_DOTS);
  Print_CMD(DISPLAY_CONTROL | DISPLAY_ON );
  Print_CMD(ENTRY_MODE_SET | ENTRY_LEFT);
  Print_CMD(CLEAR_SCREEN);
}
/*--------------------------------------------------------------------------------------------------------------*/
void Set_CGRAM(uint8_t* Char_Arr)
{
  Print_Data(Char_Arr[0]);
  Print_Data(Char_Arr[1]);
  Print_Data(Char_Arr[2]);
  Print_Data(Char_Arr[3]);
  Print_Data(Char_Arr[4]);
  Print_Data(Char_Arr[5]);
  Print_Data(Char_Arr[6]);
  Print_Data(Char_Arr[7]);
}
/*--------------------------------------------------------------------------------------------------------------*/
void Print_To_LCD(char* str)
{
  for(uint8_t i = 0; str[i] != '\0'; i++)
    Print_Data(str[i]);
}
/*--------------------------------------------------------------------------------------------------------------*/
void Print_To_LCD(const char* str)
{
  for(uint8_t i = 0; str[i] != '\0'; i++)
    Print_Data(str[i]);
}
/*--------------------------------------------------------------------------------------------------------------*/
void Print_To_LCD(int32_t num,uint8_t base)
{
  uint8_t i = 0;
  uint8_t size = floor(log10((double)num) + 1);
  char buf[size] = {'\0'};

  ltoa(num, buf, base);

  for(i = 0; i < strlen(buf); i++)
    Print_Data(buf[i]);
}
/*--------------------------------------------------------------------------------------------------------------*/