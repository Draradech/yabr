#include "stdinc.h"

#define CHANNELS 5

static char channel[CHANNELS] = {'0', '0', '0', '0', '0'};

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
         case 'c':
         {
            channel[data[0]] = data[1];
            break;
         }
      }
   }
}


#define ENTRY(ID, var, rightshift, resolution, unit, name, minvalue, maxvalue)\
case ID: sendData16(var >> rightshift); break;

void output(void)
{
   sendPacketBegin('t');
   for(uint8_t c = 0; c < CHANNELS; c++)
   {
      switch(channel[c])
      {
         #include "../mtable.inc"
      }
   }
   sendPacketEnd();
}
