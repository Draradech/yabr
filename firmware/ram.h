#ifndef _RAM_H_
#define _RAM_H_

#include "stdinc.h"

#ifdef _DEFINE_RAM_VARS_
#define global
#else
#define global extern
#endif

typedef struct SRawSensorData
{
   uint16_t   battery;
   uint16_t   sonar1;
   uint16_t   sonar2;
} SRawSensorData;

global SRawSensorData rawSensorData;

global uint8_t        lastLoopTicks;

#endif // _RAM_H_ 
