#include "stdinc.h"

#define CHANNELS 5

static char channel[CHANNELS] = {'0', '0', '0', '0', '0'};
static char pchannel = '0';

#define ENTRY(ID, var, rightshift, resolution, unit, name, minvalue, maxvalue)\
case ID: var += (int8_t)data[0]; break;

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
         case 'p':
         {
            pchannel = data[0];
            break;
         }
         case 'i':
         {
            switch(pchannel)
            {
               #include "../ptable.inc"
            }
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
         default: sendData16(-1); break;
      }
   }
   switch(pchannel)
   {
      #include "../ptable.inc"
      default: sendData16(-1); break;
   }
   sendPacketEnd();
}
