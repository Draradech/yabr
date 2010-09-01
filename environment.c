#include "stdinc.h"

void input()
{
    uint8_t command;
    uint8_t size;
    uint8_t *data;

    while(recvPacket(&command, &size, &data))
    {
        switch(command)
        {
            case 'r':
            {
                cli();
                wdt_enable(WDTO_15MS);
                for(;;);
                break;
            }
        }
    }
}

void output()
{
    sendPacketBegin('t');
    sendData(0);
    sendData('0');
    sendData('1');
    sendPacketEnd();
}
