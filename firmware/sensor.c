#include "stdinc.h"

static volatile uint16_t battery, sonar1, sonar2;
static volatile int16_t wss1, wss2;

static int8_t steps1[4][4] = {{0, 1, -1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, -1, 1, 0}};
static int8_t steps2[4][4] = {{0, -1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 1, -1, 0}};

static void readAdc(void)
{
   static uint8_t sonarTimer;
   
   ATOMIC_BLOCK(ATOMIC_FORCEON)
   {
      rawSensorData.battery = battery;
      rawSensorData.sonar1 = sonar1;
      rawSensorData.sonar2 = sonar2;
   }
   
   ADCSRA |= (1 << ADSC);
   
   PORTC &= ~(1 << PC4);
   PORTC &= ~(1 << PC5);

   sonarTimer++;
   if(sonarTimer == MS_TO_LOOP(50))
   {
      PORTC |= (1 << PC4);
   }
   else if(sonarTimer == MS_TO_LOOP(100))
   {
      sonarTimer = MS_TO_LOOP(0);
      PORTC |= (1 << PC5);
   }
}

static void readWss(void)
{
   ATOMIC_BLOCK(ATOMIC_FORCEON)
   {
      rawSensorData.wss1 = wss1;
      wss1 = 0;
      rawSensorData.wss2 = wss2;
      wss2 = 0;
   }
   speed1 = PT1(rawSensorData.wss1 * 64, speed1, 16);
   speed2 = PT1(rawSensorData.wss2 * 64, speed2, 16);
   
   pos1 += rawSensorData.wss1;
   pos2 += rawSensorData.wss2;
   
   if(speed1 > 640)
   {
      PCMSK1 = (1 << PCINT8);
      steps1[1][2] = 1;
      steps1[2][1] = 1;
   }
   else if(speed1 < -640)
   {
      PCMSK1 = (1 << PCINT9);
      steps1[1][2] = -1;
      steps1[2][1] = -1;
   }
   else
   {
      PCMSK1 = (1 << PCINT8) | (1 << PCINT9);
      steps1[1][2] = 0;
      steps1[2][1] = 0;
   }
   
   if(speed2 > 640)
   {
      PCMSK2 = (1 << PCINT17);
      steps2[1][2] = 1;
      steps2[2][1] = 1;
   }
   else if(speed2 < -640)
   {
      PCMSK2 = (1 << PCINT16);
      steps2[1][2] = -1;
      steps2[2][1] = -1;
   }
   else
   {
      PCMSK2 = (1 << PCINT16) | (1 << PCINT17);
      steps2[1][2] = 0;
      steps2[2][1] = 0;
   }
   
}

void readSensors(void)
{
   readAdc();
   readWss();
}

static force_inline uint8_t currentAdc(uint8_t admux) { return admux & 0x0f; }

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

static uint8_t pbll;
ISR(PCINT1_vect)
{
   uint8_t pb = PINB & 0x03;
   wss1 += steps1[pbll][pb];
   pbll = pb;
}

static uint8_t pcll;
ISR(PCINT2_vect)
{
   uint8_t pc = PINC & 0x03;
   wss2 += steps2[pcll][pc];
   pcll = pc;
}
