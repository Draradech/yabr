#include "stdinc.h"
#include "sounds.h"

#define POWERLIMIT 150

void actuate()
{
   int16_t powerLeft = actuator.powerLeft;
   int16_t powerRight = actuator.powerRight;

   if (attitude.voltage < 13000) actuator.deactivated = true;
   if (actuator.initCountdown) actuator.initCountdown--;

   if (attitude.angleFused > 450000 || attitude.angleFused < -450000)
   {
      if(!actuator.tempDisabled)
      {
         actuator.tempDisabled = true;
         setSound(DISABLE);
      }
   }
   else if (actuator.tempDisabled && (powerLeft + powerRight) < 20 && (powerLeft + powerRight) > -20 && !actuator.initCountdown)
   {
      actuator.tempDisabled = false;
      setSound(ENABLE);
   }

   if (powerLeft < 0 && !actuator.deactivated && !actuator.tempDisabled)
   {
      PORTC |=  (1 << PC2);
      PORTC &= ~(1 << PC3);
      OCR2A = MIN(-powerLeft, POWERLIMIT);
   }
   else if (powerLeft > 0 && !actuator.deactivated && !actuator.tempDisabled)
   {
      PORTC &= ~(1 << PC2);
      PORTC |=  (1 << PC3);
      OCR2A = MIN(powerLeft, POWERLIMIT);
   }
   else
   {
      PORTC &= ~(1 << PC2);
      PORTC &= ~(1 << PC3);
      OCR2A = 0;
   }

   if (powerRight < 0 && !actuator.deactivated && !actuator.tempDisabled)
   {
      PORTB |=  (1 << PB2);
      PORTB &= ~(1 << PB3);
      OCR2B = MIN(-powerRight, POWERLIMIT);
   }
   else if (powerRight > 0 && !actuator.deactivated && !actuator.tempDisabled)
   {
      PORTB &= ~(1 << PB2);
      PORTB |=  (1 << PB3);
      OCR2B = MIN(powerRight, POWERLIMIT);
   }
   else
   {
      PORTB &= ~(1 << PB2);
      PORTB &= ~(1 << PB3);
      OCR2B = 0;
   }
}
