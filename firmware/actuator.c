#include "stdinc.h"

void actuate(void)
{
   if(pwm1 > 0)
   {
      PORTB &= ~(1 << PB2);
      PORTB |=  (1 << PB3);
      OCR2B = (uint8_t)pwm1;
   }
   else
   {
      PORTB &= ~(1 << PB3);
      PORTB |=  (1 << PB2);
      OCR2B = (uint8_t)(-pwm1);
   }
   
   if(pwm2 > 0)
   {
      PORTC &= ~(1 << PC2);
      PORTC |=  (1 << PC3);
      OCR2A = (uint8_t)pwm2;
   }
   else
   {
      PORTC &= ~(1 << PC3);
      PORTC |=  (1 << PC2);
      OCR2A = (uint8_t)(-pwm2);
   }
   
}
