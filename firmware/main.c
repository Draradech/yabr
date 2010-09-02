#include "stdinc.h"

static volatile bool loopActive;
static volatile uint8_t ticksSinceLoopStart;

void __attribute__((noreturn)) main(void)
{
    init();
    
    for(;;)
    {
        while(!loopActive)
        {
            ; // wait for next loop
        }
		
		readSensors();
        
        input();

        output();
        
        cli();
        lastLoopTicks = ticksSinceLoopStart;
        loopActive = false;
        sei();
    }
}

ISR(TIMER0_COMPA_vect)
{
    // Mainloop Control
    ticksSinceLoopStart++;
    if(loopActive == false && ticksSinceLoopStart >= TICKS_PER_LOOP)
    {
        ticksSinceLoopStart = 0;
        loopActive = true;
    }
}
