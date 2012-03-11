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
   int16_t   voltage;
   int16_t   sonar1;
   int16_t   sonar2;
   int16_t   wssRight;
   int16_t   wssLeft;
   int32_t   position;
   int16_t   diffSide;
   int16_t   longAcc;
   int16_t   latAcc;
   int16_t   vertAcc;
   int16_t   angleRate;
} SRawSensorData;

typedef struct
{
    int16_t angleRate;
    int16_t subAngleRate;
    
    int16_t angle;

    int16_t longAcc;
    int16_t latAcc;
    int16_t vertAcc;
} SSensorOffsets;

typedef struct
{
    // converted and filtered sensor values
    int32_t angleRate;      // LSB: 0.0001 °/s

    int16_t longAcc;        // LSB: 0.001 m/ss
    int16_t latAcc;         // LSB: 0.001 m/ss
    int16_t vertAcc;        // LSB: 0.001 m/ss

    int16_t voltage;        // LSB: 0.001 V

    int16_t speedRight;     // LSB: 0.001 m/s
    int16_t speedLeft;      // LSB: 0.001 m/s
    int16_t speed;          // LSB: 0.001 m/s
    int32_t position;       // LSB: 0.001 m
    int16_t diffSide;       // LSB: 0.001 m

    int32_t angleAcc;       // LSB: 0.0001 °
    int32_t angleGyro;      // LSB: 0.0001 °
    int32_t angleFused;     // LSB: 0.0001 °
} SAttitude;

typedef struct
{
    int16_t powerLeft;
    int16_t powerRight;

    int8_t  deactivated;
    int8_t  tempDisabled;
    uint8_t initCountdown;
} SActuator;

typedef struct
{
    int16_t angleBySpeed;
    int16_t angleByPosition;
    int16_t powerByAngleDiv;
    int16_t powerByAngleRateDiv;
} SControlPara;

typedef struct
{
    int32_t angleBySpeed;
    int32_t angleByPosition;
    int32_t angleTarget;
} SControl;

global SControl control;
global SControlPara controlPara;
global SActuator actuator;
global SRawSensorData rawSensorData;
global SSensorOffsets sensorOffsets;
global SAttitude attitude;

global uint8_t lastLoopTicks;

#endif // _RAM_H_ 
