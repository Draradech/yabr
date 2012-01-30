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
   int16_t    wss1;
   int16_t    wss2;
} SRawSensorData;

global SRawSensorData rawSensorData;

global uint8_t        lastLoopTicks;

global int16_t pwm1;
global int16_t pwm2;

global int16_t speed1;
global int16_t speed2;

global int16_t pos1;
global int16_t pos2;

#endif // _RAM_H_ 
