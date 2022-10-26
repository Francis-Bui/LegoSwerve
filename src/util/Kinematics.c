#include "Constants.c"
#include <stdlib.h>
#include <math.h>

float moduleAngleSpeed[2];
float wheelDriveSpeed[4];


float getWheelAngles() 
{   
    float wheelAngles[2];
    wheelAngles[0] = moduleAngleSpeed[0];
    wheelAngles[1] = moduleAngleSpeed[1];

    return *wheelAngles;
}

float getWheelVelocities() 
{
    float wheelVelocities[2];
    wheelVelocities[0] = wheelDriveSpeed[1];
    wheelVelocities[1] = wheelDriveSpeed[3];
    return *wheelVelocities;
}

void scalePowers() 
{
    float maxPower = 0;
    for (int i = 0; i < 2; i++) 
    {
        if (fabs(wheelDriveSpeed[0]) > maxPower)
            maxPower = fabs(wheelDriveSpeed[0]);
        if (fabs(wheelDriveSpeed[1]) > maxPower)
            maxPower = fabs(wheelDriveSpeed[1]);
    }
    if (maxPower > 1.0) 
    {
        wheelDriveSpeed[0] /= maxPower;
        wheelDriveSpeed[1] /= maxPower;
    }
}

void calculateKinematics(float rotationPower, float strafePower, float forwardPower)
{
    if (rotationPower != 0 || strafePower != 0 || forwardPower != 0) 
    {

        float v1X = strafePower;
        float v1Y = forwardPower - rotationPower * trackWidth / 2.0;

        float v2X = strafePower;
        float v2Y = forwardPower + rotationPower * trackWidth / 2.0;

        moduleAngleSpeed[0] = atan2(v1Y, v1X); // module 1 angle
        wheelDriveSpeed[0] = hypot(v1Y, v1X); // module 1 speed

        moduleAngleSpeed[1] = atan2(v2Y, v2X); // module 2 angle
        wheelDriveSpeed[2] = hypot(v2Y, v2X); // module 2 speed

        scalePowers();
    }
}

