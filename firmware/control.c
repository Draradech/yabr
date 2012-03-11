#include "stdinc.h"

void controlAlgo(void)
{
   int32_t angleDiff;
   int16_t byAngle, byRate;

   control.angleBySpeed = (int32_t)(attitude.speedLeft + attitude.speedRight) * controlPara.angleBySpeed;
   control.angleByPosition = attitude.position * controlPara.angleByPosition;
   control.angleTarget = control.angleBySpeed + control.angleByPosition;

   angleDiff = (attitude.angleFused - control.angleTarget );
   byAngle = angleDiff / controlPara.powerByAngleDiv / 16;
   byRate = attitude.angleRate / controlPara.powerByAngleRateDiv / 256;

   actuator.powerLeft = byAngle + byRate + attitude.diffSide;
   actuator.powerRight = byAngle + byRate - attitude.diffSide;
}
