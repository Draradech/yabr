#include "stdinc.h"
#include "sounds.h"

void actuate()
{
   actuator.powerLeft = actuator.powerRight = attitude.angleFused / 1024 + 18;


	if (attitude.voltage < 13000) actuator.deactivated = true;
	if (actuator.initCountdown) actuator.initCountdown--;

   if (attitude.angleFused > 300000 || attitude.angleFused < -300000)
	{
	   if(!actuator.tempDisabled)
	   {
	      actuator.tempDisabled = true;
	      setSound(DISABLE);
	   }
	}
	else if (actuator.tempDisabled && (actuator.powerLeft + actuator.powerRight) < 10 && (actuator.powerLeft + actuator.powerRight) > -10 && !actuator.initCountdown)
	{
		actuator.tempDisabled = false;
		setSound(ENABLE);
	}

	if (actuator.powerLeft < 0 && !actuator.deactivated && !actuator.tempDisabled)
	{
		PORTC |=  (1 << PC2);
		PORTC &= ~(1 << PC3);
		OCR2A = MIN(-actuator.powerLeft, 255);
	}
	else if (actuator.powerLeft > 0 && !actuator.deactivated && !actuator.tempDisabled)
	{
		PORTC &= ~(1 << PC2);
		PORTC |=  (1 << PC3);
		OCR2A = MIN(actuator.powerLeft, 255);
	}
	else
	{
		PORTC &= ~(1 << PC2);
		PORTC &= ~(1 << PC3);
		OCR2A = 0;
	}

	if (actuator.powerRight < 0 && !actuator.deactivated && !actuator.tempDisabled)
	{
		PORTB |=  (1 << PB2);
		PORTB &= ~(1 << PB3);
		OCR2B = MIN(-actuator.powerRight, 255);
	}
	else if (actuator.powerRight > 0 && !actuator.deactivated && !actuator.tempDisabled)
	{
		PORTB &= ~(1 << PB2);
		PORTB |=  (1 << PB3);
		OCR2B = MIN(actuator.powerRight, 255);
	}
	else
	{
		PORTB &= ~(1 << PB2);
		PORTB &= ~(1 << PB3);
		OCR2B = 0;
	}
}
