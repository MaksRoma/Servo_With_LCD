#include "Display.h"
#include <Servo.h>
#define Servo_Out 9
/*--------------------------------------------------------------------------------------------------------------*/
Servo myservo;  // create servo object to control a servo
uint8_t potpin = A0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin
int angle;    // the angle servo is sent to
float EMA_a = 1;      //initialization of EMA alpha
int EMA_S = 0;          //initialization of EMA S
/*--------------------------------------------------------------------------------------------------------------*/
void setup()
{
  Serial.begin(9600);

  pinMode(RS,OUTPUT);
  pinMode(E,OUTPUT);

  pinMode(DB4,OUTPUT);
  pinMode(DB5,OUTPUT);
  pinMode(DB6,OUTPUT);
  pinMode(DB7,OUTPUT);

  pinMode(Servo_Out,OUTPUT);


  LCD_Setup();
  // myservo.attach(9);  
  EMA_S = analogRead(potpin);
  
  //SetCursor(0,0);
  Print_CMD(SET_DDRAM_ADDR | 0x0);
  Print_To_LCD("Robojax Servo");
  Print_CMD(SET_DDRAM_ADDR | 0x40);
  Print_To_LCD("Knob");
  delay(2000);

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
  val = analogRead(potpin);
  EMA_S = (EMA_a*val) + ((1-EMA_a)*EMA_S);
  Serial.println(EMA_S);
  angle = map(EMA_S, 0, 1023, 0, 180);
  analogWrite(Servo_Out, angle);
  // myservo.write(angle); 
 
  Print_CMD(SET_DDRAM_ADDR | 0xB);
  Print_To_LCD("    ");
  Print_CMD(SET_DDRAM_ADDR | 0xB);
  Print_To_LCD((int32_t)val);

  Print_CMD(SET_DDRAM_ADDR | 0x4B);
  Print_To_LCD("   ");
  Print_CMD(SET_DDRAM_ADDR | 0x4B);
  Print_To_LCD((int32_t)angle);

  delay(500);
}
/*--------------------------------------------------------------------------------------------------------------*/