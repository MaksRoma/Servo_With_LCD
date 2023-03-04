#include <stdint.h>
#include "Arduino.h"
#include "Display.h"
/*--------------------------------------------------------------------------------------------------------------*/
inline void latching()
{
  delayMicroseconds(750);
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
  PORTD = (data & 0xF0);
  latching();
  //print LSB 4 bits
  PORTD = ((data << 4) & 0xF0);
  latching();}
/*--------------------------------------------------------------------------------------------------------------*/
void Print_CMD(uint8_t cmd)
{
  digitalWrite(RS, LOW);
  //print MSB 4 bits
  PORTD = (cmd & 0xF0);
  latching();
  //print LSB 4 bits
  PORTD = ((cmd << 4) & 0xF0);
  latching();  
}
/*--------------------------------------------------------------------------------------------------------------*/
void LCD_Setup()
{
  delay(100);

  digitalWrite(RS, LOW);
  //Sets to 4-bit operation. otherwise, next instructions will be wrong execute
  PORTD = (0x3 << 4) & 0xF0;
  latching();
  delay(5);
  PORTD = (0x3 << 4) & 0xF0;
  latching();
  delayMicroseconds(100);
  PORTD = (0x3 << 4) & 0xF0;
  latching();
  delayMicroseconds(100);

  PORTD = (0x2 << 4) & 0xF0;
  latching();
  delayMicroseconds(100);
  Print_CMD(0x28);
  Print_CMD(0x0C);
  Print_CMD(0x06);
  Print_CMD(0x01);
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