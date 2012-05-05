#include "stdinc.h"

static volatile uint16_t voltage = 789;
static volatile uint16_t sonar1, sonar2;
static volatile int16_t wssRight, wssLeft;

static int8_t stepsRight[4][4] = {{0, 0, -1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, -1, 2, 0}};
//static int8_t stepsRight[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
static int8_t stepsLeft[4][4] = {{0, -1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 1, -1, 0}};
//static int8_t stepsLeft[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

static uint8_t spiSendRecv(uint8_t byte)
{
   SPDR = byte;
   while(!(SPSR & (1 << SPIF)));
   return SPDR;
}

#define GyroRefusal           (highbyte & (1 << 7))
#define GyroEndOfConversion   (highbyte & (1 << 5))
static void readGyro(void)
{
   uint8_t highbyte;
   uint8_t lowbyte;

   PORTC &= ~(1 << PC6); // select Gyro

   spiSendRecv(0x94);
   highbyte = spiSendRecv(0);
   lowbyte = spiSendRecv(0);

   if(!GyroRefusal)
   {
      do
      {
         spiSendRecv(0x80);
         highbyte = spiSendRecv(0);
         lowbyte = spiSendRecv(0);
      } while (!GyroRefusal && !GyroEndOfConversion);

      if(!GyroRefusal && GyroEndOfConversion)
      {
         rawSensorData.angleRate = -(((((highbyte & 0x0f) << 8) | lowbyte) >> 1) + sensorOffsets.angleRate);
      }
   }

   PORTC |= (1 << PC6); // unselect Gyro
}

static void readAcc(void)
{
   uint8_t highbyte;
   uint8_t lowbyte;

   PORTC &= ~(1 << PC7); // select Acc

   spiSendRecv(0x24);
   highbyte = spiSendRecv(0);
   lowbyte = spiSendRecv(0);

   rawSensorData.latAcc = ((int16_t)(((uint16_t)highbyte) << 8) | lowbyte) >> 3;
   rawSensorData.latAcc += sensorOffsets.latAcc;

   highbyte = spiSendRecv(0);
   lowbyte = spiSendRecv(0);

   rawSensorData.vertAcc = ((int16_t)(((uint16_t)highbyte) << 8) | lowbyte) >> 3;
   rawSensorData.vertAcc += sensorOffsets.vertAcc;

   highbyte = spiSendRecv(0);
   lowbyte = spiSendRecv(0);

   rawSensorData.longAcc = -(((int16_t)(((uint16_t)highbyte) << 8) | lowbyte) >> 3);
   rawSensorData.longAcc += sensorOffsets.longAcc;

   PORTC |= (1 << PC7); // unselect Acc
}

static void readAdc(void)
{
   static uint8_t sonarTimer;

   ATOMIC_BLOCK(ATOMIC_FORCEON)
   {
      rawSensorData.voltage = voltage;
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
   if(attitude.speedRight > 1000)
   {
      PCMSK1 = (1 << PCINT8);
      stepsRight[1][2] = 1;
      stepsRight[2][1] = 1;
   }
   else if(attitude.speedRight < -1000)
   {
      PCMSK1 = (1 << PCINT9);
      stepsRight[1][2] = -1;
      stepsRight[2][1] = -1;
   }
   else
   {
      PCMSK1 = (1 << PCINT8) | (1 << PCINT9);
      stepsRight[1][2] = 0;
      stepsRight[2][1] = 0;
   }

   if(attitude.speedLeft > 1000)
   {
      PCMSK2 = (1 << PCINT17);
      stepsLeft[1][2] = 1;
      stepsLeft[2][1] = 1;
   }
   else if(attitude.speedLeft < -1000)
   {
      PCMSK2 = (1 << PCINT16);
      stepsLeft[1][2] = -1;
      stepsLeft[2][1] = -1;
   }
   else
   {
      PCMSK2 = (1 << PCINT16) | (1 << PCINT17);
      stepsLeft[1][2] = 0;
      stepsLeft[2][1] = 0;
   }

   ATOMIC_BLOCK(ATOMIC_FORCEON)
   {
      rawSensorData.wssRight = wssRight;
      wssRight = 0;
      rawSensorData.wssLeft = wssLeft;
      wssLeft = 0;
   }

   rawSensorData.position += rawSensorData.wssRight + rawSensorData.wssLeft;
   rawSensorData.diffSide += rawSensorData.wssRight - rawSensorData.wssLeft;

   if (attitude.angleFused > 450000 || attitude.angleFused < -450000)
   {
      rawSensorData.position = 0;
      rawSensorData.diffSide = 0;
   }
}

void readSensors(void)
{
   readAdc();
   readWss();
   readGyro();
   readAcc();
}

static force_inline uint8_t currentAdc(uint8_t admux) { return admux & 0x0f; }
ISR(ADC_vect)
{
   uint8_t admux = ADMUX;

   if(currentAdc(admux) == 0)
   {
      voltage = ADC;
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
   wssRight += stepsRight[pbll][pb];
   pbll = pb;
}

static uint8_t pcll;
ISR(PCINT2_vect)
{
   uint8_t pc = PINC & 0x03;
   wssLeft += stepsLeft[pcll][pc];
   pcll = pc;
}
