#include "stdinc.h"

void attitudeCalculation(void)
{
   int32_t tmp;

   tmp = (int32_t) rawSensorData.voltage * 5367 >> 8;     // * 21469 (21,469V) / 1024
   attitude.voltage = PT1(tmp, attitude.voltage, 16);

   tmp = (int32_t) rawSensorData.angleRate * 750000 >> 8; // * 3000000 (300°/s) / 1024
   attitude.angleRate = PT1(tmp, attitude.angleRate, 4);

   tmp = (int32_t) rawSensorData.longAcc * 1884 >> 8;     // * 9810 (1g) / 1333
   attitude.longAcc = PT1(tmp, attitude.longAcc, 16);

   tmp = (int32_t) rawSensorData.latAcc * 1884 >> 8;      // * 9810 (1g) / 1333
   attitude.latAcc = PT1(tmp, attitude.latAcc, 16);

   tmp = (int32_t) rawSensorData.vertAcc * 1884 >> 8;     // * 9810 (1g) / 1333
   attitude.vertAcc = PT1(tmp, attitude.vertAcc, 16);

   tmp = (int16_t) rawSensorData.wssRight * 133;          // * 1000 (1 m/s) / (3750 / 500)
   attitude.speedRight = PT1(tmp, attitude.speedRight, 16);

   tmp = (int16_t) rawSensorData.wssLeft * 133;           // * 1000 (1 m/s) / (3750 / 500)
   attitude.speedLeft = PT1(tmp, attitude.speedLeft, 16);

   tmp = (int16_t) (attitude.speedRight + attitude.speedLeft) / 2;
   attitude.speed = PT1(tmp, attitude.speed, 16);

   tmp = (int32_t) rawSensorData.position * 2 / 15;
   attitude.position = tmp;

   tmp = (int32_t) rawSensorData.diffSide * 2 / 15;
   attitude.diffSide = tmp;

   attitude.angleAcc = (int32_t)-100 * (atan2_cordic(attitude.longAcc, attitude.vertAcc) + sensorOffsets.angle);
   if(actuator.initCountdown == 24)
   {
      attitude.angleGyro = attitude.angleAcc;
      attitude.angleFused = attitude.angleAcc;
   }

   tmp = attitude.angleRate * 134 >> 16; // / LOOPS_PER_SECOND;
   attitude.angleGyro += tmp;
   attitude.angleFused += tmp;

   tmp = attitude.angleAcc;
   attitude.angleFused = PT1(tmp, attitude.angleFused, 512);

   if(attitude.angleGyro < attitude.angleFused)
   {
      sensorOffsets.subAngleRate--;
   }
   else if(attitude.angleGyro > attitude.angleFused)
   {
      sensorOffsets.subAngleRate++;
   }

   if(sensorOffsets.subAngleRate > 1000)
   {
      sensorOffsets.angleRate++;
      sensorOffsets.subAngleRate = 0;
      attitude.angleGyro = attitude.angleFused;
   }

   if(sensorOffsets.subAngleRate < -1000)
   {
      sensorOffsets.angleRate--;
      sensorOffsets.subAngleRate = 0;
      attitude.angleGyro = attitude.angleFused;
   }
}
