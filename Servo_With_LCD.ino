#include "Display.h"
#include "Custom_Servo.h"
/*--------------------------------------------------------------------------------------------------------------*/
uint8_t potpin = A0;  // analog pin used to connect the potentiometer
short val = 0;    // variable to read the value from the analog pin
short angle = 0;
/*--------------------------------------------------------------------------------------------------------------*/
void setup()
{
  pinMode(RS,OUTPUT);
  pinMode(E,OUTPUT);
  pinMode (T_BASE, OUTPUT);

  pinMode(DB4,OUTPUT);
  pinMode(DB5,OUTPUT);
  pinMode(DB6,OUTPUT);
  pinMode(DB7,OUTPUT);

  pinMode(Servo_Out,OUTPUT);

  //digitalWrite(T_BASE,HIGH);
  // delay(100);
  pinMode (T_BASE, LOW);
  delay(200);
  digitalWrite(T_BASE,HIGH);

  LCD_Setup();
  Servo_Setup();

  /*ADC Setup*/
  ADMUX = 0x40; //ADC0 channel, AVCC voltage reference
  ADCSRA |= (1 << ADEN); //enable ADC


  Print_CMD(CLEAR_SCREEN);
  //SetCursor(0,0);
  Print_CMD(SET_DDRAM_ADDR | 0x0);
  Print_To_LCD("Pot. Value:");
  //SetCursor(1,0);
  Print_CMD(SET_DDRAM_ADDR | 0x40);
  Print_To_LCD("Angle     :");
}
/*--------------------------------------------------------------------------------------------------------------*/
void loop()
{

  //start conversion
  ADCSRA |= (1 << ADSC);

  // Wait for conversion to complete
  while (ADCSRA & (1 << ADSC));
  
  //read ADC result
  val = ADC;
  /*************************************************************************************************************
  conversion from in_min-in_max range to out_min-out_max range
  y = m * x + b
  m = (out_max - out_min) / (in_max - in_min) 
  b = out_min = 544
  **************************************************************************************************************/
  angle = 1.865 * val + 544; //conversion from 0-1023 range to 544-2400 range
  OCR1A = angle;  


  Print_CMD(SET_DDRAM_ADDR | 0xB);
  Print_To_LCD("    ");
  Print_CMD(SET_DDRAM_ADDR | 0xB);
  Print_To_LCD((int32_t)val);

  Print_CMD(SET_DDRAM_ADDR | 0x4B);
  Print_To_LCD("    ");
  Print_CMD(SET_DDRAM_ADDR | 0x4B);
  Print_To_LCD((int32_t)angle);

  delay(500);
}
/*--------------------------------------------------------------------------------------------------------------*/


