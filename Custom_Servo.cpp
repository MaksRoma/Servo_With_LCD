#include "Custom_Servo.h"
#include "Arduino.h"


void Servo_Setup()
{
//_BV macro desription:
//#define _BV(bit) (1 << (bit))
  pinMode(Servo_Out, OUTPUT);
  TCCR1B = 0;
  TCCR1A = 0;
  //set Prescaler to 8 (Timer clock: 2MHz)
  //PWM mode: 10 (PWM,phase correct)
  TCCR1B |= _BV(WGM13) | _BV(CS11);
  TCCR1B &= (~_BV(WGM12)); //~(1 << WGM12);
  TCCR1A |= _BV(WGM11) | _BV(COM1A1);
  TCCR1A &= (~_BV(WGM10)) & (~_BV(COM1A0)); //~(1 << WGM10) & ~(1 << COM1A0);
  ICR1 = 20000;
}