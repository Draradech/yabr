#include "stdinc.h"
#include "sounds.h"

void actuate()
{
   int16_t powerLeft, powerRight, powerLimit;

   //powerLimit = 0;
   powerLimit = (int32_t)150 * 16000 / attitude.voltage;
   powerLeft = (int32_t)actuator.powerLeft * 16000 / attitude.voltage;
   powerRight = (int32_t)actuator.powerRight * 16000 / attitude.voltage;

   if (attitude.voltage < 12000) actuator.deactivated = true;
   if (actuator.initCountdown) actuator.initCountdown--;

   if (  attitude.angleFused >  450000
      || attitude.angleFused < -450000
      || attitude.speedRight >    4000
      || attitude.speedLeft  >    4000
      || attitude.speedRight <   -4000
      || attitude.speedLeft  <   -4000
      )
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

   if(actuator.tempDisabled)
   {
      //if(gcontrol.countdown)
      if(false)
      {
         powerLeft = gcontrol.speed + gcontrol.rl/4;
         powerRight = gcontrol.speed - gcontrol.rl/4;
      }
      else
      {
         powerLeft = powerRight = 0;
      }
   }

   if (powerLeft < 0 && !actuator.deactivated)
   {
      PORTC |=  (1 << PC2);
      PORTC &= ~(1 << PC3);
      OCR2A = MIN(-powerLeft, powerLimit);
   }
   else if (powerLeft > 0 && !actuator.deactivated)
   {
      PORTC &= ~(1 << PC2);
      PORTC |=  (1 << PC3);
      OCR2A = MIN(powerLeft, powerLimit);
   }
   else
   {
      PORTC &= ~(1 << PC2);
      PORTC &= ~(1 << PC3);
      OCR2A = 0;
   }

   if (powerRight < 0 && !actuator.deactivated)
   {
      PORTB |=  (1 << PB2);
      PORTB &= ~(1 << PB3);
      OCR2B = MIN(-powerRight, powerLimit);
   }
   else if (powerRight > 0 && !actuator.deactivated)
   {
      PORTB &= ~(1 << PB2);
      PORTB |=  (1 << PB3);
      OCR2B = MIN(powerRight, powerLimit);
   }
   else
   {
      PORTB &= ~(1 << PB2);
      PORTB &= ~(1 << PB3);
      OCR2B = 0;
   }
}
