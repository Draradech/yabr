#include "stdinc.h"

void init(void)
{
   // PA0 - ADC0 - Battery

   // PA1 - ADC1 - MaxSonar 1

   // PA2 - ADC2 - MaxSonar 2

   // PA3

   // PA4

   // PA5

   // PA6

   // PA7

   // PB0 - M1 LSA

   // PB1 - M1 LSB

   // PB2 - M1 A
   DDRB |= (1 << PB2);

   // PB3 - M1 B
   DDRB |= (1 << PB3);

   // PB4
   DDRB |= (1 << PB4);    // has to be output or high for SPI master mode

   // PB5 - MOSI
   DDRB |= (1 << PB5);

   // PB6 - MISO

   // PB7 - SCK
   DDRB |= (1 << PB7);

   // PC0 - M2 LSA

   // PC1 - M2 LSB

   // PC2 - M2 A
   DDRC |= (1 << PC2);

   // PC3 - M2 B
   DDRC |= (1 << PC3);

   // PC4 - MaxSonar 1 RX
   DDRC |= (1 << PC4);

   // PC5 - MaxSonar 2 RX
   DDRC |= (1 << PC5);

   // PC6 - Gyro SS
   DDRC  |= (1 << PC6);
   PORTC |= (1 << PC6);        // ! Gyro Select

   // PC7 - Acc SS
   DDRC  |= (1 << PC7);
   PORTC |= (1 << PC7);        // ! Acc Select

   // PD0 - RX

   // PD1 - TX

   // PD2

   // PD3

   // PD4

   // PD5 - OC1A - Speaker (enabled by soundplayer when needed)

   // PD6 - OC2B - M1 PWM
   DDRD |= (1 << PD6);

   // PD7 - OC2A - M2 PWM
   DDRD |= (1 << PD7);

   // ADC
   ADMUX  = (1 << REFS0);      // AVCC with external cap
   ADCSRA = (1 << ADEN)        // ADC Enabled
          | (1 << ADIE)        // ADC Conversion Complete Interrupt
          | (1 << ADPS0)
          | (1 << ADPS1)
          | (1 << ADPS2);      // prescalar 128
   DIDR0  = 0xFF;              // disable digital inputs for ADC pins

   // PCINT
   PCICR  = (1 << PCIE1)
          | (1 << PCIE2);      // pin change interrupts for ports B and C
   PCMSK1 = (1 << PCINT8)      // pin change interrupt for PB0
          | (1 << PCINT9);     // pin change interrupt for PB1
   PCMSK2 = (1 << PCINT16)     // pin change interrupt for PC0
          | (1 << PCINT17);    // pin change interrupt for PC1

   // SPI
   SPCR = (1 << SPE)           // SPI enable
        | (1 << MSTR)          // SPI Master mode
        | (1 << SPR0);         // 1,25 MHz SPI clock

   // UART (already initialized by bootloader)
   UCSR0B |= (1 << RXCIE0);    // RX Complete Interrupt

   // Timer 0 - Mainloop
   TCCR0A = (1 << WGM01);      // CTC mode,
   TCCR0B = (1 << CS01);
   OCR0A  = 50 - 1;             // Prescalar 8, TOP 50 -> 50000 Hz
    
   TIMSK0 = (1 << OCIE0A);     // Output compare interrupt enable

   // Timer 1 - frequency generation on OC1A (Speaker)
   TCCR1A = (1 << COM1A0);     // toggle on compare match
   TCCR1B = (1 << WGM12)       // CTC with OCR1A
          | (1 << CS11);       // prescalar 8

   // Timer 2 - 2x PWM
   TCCR2A = (1 << COM2A1)
          | (1 << COM2B1)
          | (1 << WGM20);      // non-inverting phase-correct PWM mode

   TCCR2B = (1 << CS20)
          | (1 << CS22);       // Prescalar 32 -> ~1,2khz PWM

   // Ram Vars
   attitude.voltage =  14800;          // initialize battery voltage to lipo nominal
   actuator.initCountdown = 48;
   actuator.tempDisabled = true;
   
   sensorOffsets.angleRate = -1024;    // initialize gyro offset (self learning)
   sensorOffsets.longAcc = 180;
   sensorOffsets.latAcc = 70;
   sensorOffsets.vertAcc = -95;
   sensorOffsets.angle = -210;
   
   controlPara.angleBySpeed = -20;
   controlPara.angleByPosition = -55;
   controlPara.powerByAngleDiv = 50;
   controlPara.powerByAngleRateDiv = 60;

   // Enable Interrupts
   sei();
}
