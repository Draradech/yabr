#include "stdinc.h"

void input(void)
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

void output(void)
{
    sendPacketBegin('t');
    sendData(HIGH(rawSensorData.battery));
    sendData(LOW(rawSensorData.battery));
    sendData(HIGH(rawSensorData.sonar1));
    sendData(LOW(rawSensorData.sonar1));
    sendData(HIGH(rawSensorData.sonar2));
    sendData(LOW(rawSensorData.sonar2));
	sendData(0);
	sendData(lastLoopTicks);
    sendPacketEnd();
}
