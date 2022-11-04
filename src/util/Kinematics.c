#include "Constants.c"

float hypot(float x, float y);

float moduleAngleSpeed[2];
float wheelDriveSpeed[4];

float* getWheelAngles()
{
    float wheelAngles[2];
    wheelAngles[0] = moduleAngleSpeed[0];
    wheelAngles[1] = moduleAngleSpeed[1];

    return &wheelAngles;
}

float* getWheelVelocities()
{
    float wheelVelocities[2];
    wheelVelocities[0] = wheelDriveSpeed[1];
    wheelVelocities[1] = wheelDriveSpeed[3];
    return &wheelVelocities;
}


float hypot(float x, float y)
{
	return sqrt(pow(x,2) + pow(y,2));
}
