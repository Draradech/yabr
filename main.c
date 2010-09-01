#include "stdinc.h"

static volatile bool loopActive;
static volatile uint8_t ticksSinceLoopStart;

void main(void) __attribute__((noreturn));
void main(void)
{
    init();
    
    for(;;)
    {
        while(!loopActive)
        {
            ; // wait for next loop
        }
        
        input();

        output();
        
        cli();
        lastLoopTicks = ticksSinceLoopStart;
        loopActive = false;
        sei();
    }
}

ISR(TIMER2_COMPA_vect)
{
    // Mainloop Control
    ticksSinceLoopStart++;
    if(loopActive == false && ticksSinceLoopStart >= TICKS_PER_LOOP)
    {
        ticksSinceLoopStart = 0;
        loopActive = true;
    }
}
