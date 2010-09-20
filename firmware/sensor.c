#include "stdinc.h"

static volatile uint16_t battery, sonar1, sonar2;

static void readAdc(void)
{
	static uint8_t sonarTimer;
	
	rawSensorData.battery = battery;
	rawSensorData.sonar1 = sonar1;
	rawSensorData.sonar2 = sonar2;

	ADCSRA |= (1 << ADSC);
	
	sonarTimer++;
	if(sonarTimer == MS_TO_LOOP(50))
	{
		PORTC |= (1 << PC4);
		_delay_us(30);
		PORTC &= ~(1 << PC4);
	}
	else if(sonarTimer == MS_TO_LOOP(100))
	{
		sonarTimer = MS_TO_LOOP(0);
		PORTC |= (1 << PC5);
		_delay_us(30);
		PORTC &= ~(1 << PC5);
	}
	else
	{
		// near-constant runtime, please
		_delay_us(30);
	}
}

void readSensors(void)
{
	readAdc();
}

static inline uint8_t currentAdc(uint8_t admux) { return admux & 0x0f; }

ISR(ADC_vect)
{
	uint8_t admux = ADMUX;
	
	if(currentAdc(admux) == 0)
	{
		battery = ADC;
		ADMUX = (admux & 0xf0) | 0x01;
		ADCSRA |= (1 << ADSC);
	}
	else if(currentAdc(admux) == 1)
	{
		sonar1 = ADC;
		ADMUX = (admux & 0xf0) | 0x02;
		ADCSRA |= (1 << ADSC);
	}
	else if(currentAdc(admux) == 2)
	{
		sonar2 = ADC;
		ADMUX = (admux & 0xf0) | 0x00;
	}
}

ISR(PCINT1_vect)
{
}

ISR(PCINT2_vect)
{
}