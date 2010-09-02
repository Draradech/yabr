#include "stdinc.h"

void init()
{
    // PA0

    // PA1

    // PA2

    // PA3

    // PA4

    // PA5

    // PA6

    // PA7

    // PB0

    // PB1

    // PB2

    // PB3

    // PB4

    // PB5

    // PB6

    // PB7

    // PC0

    // PC1

    // PC2

    // PC3

    // PC4

    // PC5

    // PC6

    // PC7

    // PD0 - RX
    UCSR0B |= (1 << RXCIE0);    // RX Complete Interrupt

    // PD1 - TX

    // UART - already initialized by bootloader

    // PD2

    // PD3

    // PD4

    // PD5

    // PD6

    // PD7

    // Timer 0 - Mainloop
    TCCR0A |= (1 << WGM01);     // CTC mode,
    TCCR0B |= (1 << CS01);
    OCR0A = 50 - 1;             // Prescalar 8, TOP 50 -> 50000 Hz
     
    TIMSK0 |= (1 << OCIE0A);    // Output compare interrupt enable

    // Enable Interrupts
    sei();
}
