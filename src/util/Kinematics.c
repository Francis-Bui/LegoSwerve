#include "Constants.c"
#include "Vec2.c"


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

float* getMotorPowers(float clockwiseP, float forwardP)
{
    Vec2 powerVec = Vec2_createVector(clockwiseP, forwardP);
    
    Vec2 mOneUVec = Vec2_createVector(1/sqrt(2), 1/sqrt(2));
    Vec2 mTwoUVec = Vec2_createVector(-1/sqrt(2), 1/sqrt(2));


}

float hypot(float x, float y)
{
	return sqrt(pow(x,2) + pow(y,2));
}
