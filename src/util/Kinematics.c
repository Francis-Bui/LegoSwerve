#include "Constants.c"
#include "Vec2.c"

float* getMotorPowers(float clockwiseP, float forwardP);
void normalizeMotorVectors(Vec2 *m1, Vec2 *m2);
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

    Vec2 mOneResultant = Vec2_projectOnto(powerVec, mOneUVec);
    Vec2 mTwoResultant = Vec2_projectOnto(powerVec, mTwoUVec);
    Vec2_scale(&mOneResultant, sqrt(2));
    vec2_scale(&mTwoResultant, sqrt(2));
    normalizeMotorVectors(&mOneResultant, &mTwoResultant);

    float motorPowers[2] = {0};
    motorPowers[0] = mOneResultant.magnitude;
    motorPowers[1] = mTwoResultant.magnitude;
    return motorPowers;
}

float hypot(float x, float y)
{
	return sqrt(pow(x,2) + pow(y,2));
}

/**
 * Takes in two motor vectors and makes sure they don't exceed.
 * the possible motor power for them individually. If they do, both vectors are scaled
 * down proportionally.  
*/
void normalizeMotorVectors(Vec2 *m1, Vec2 *m2)
{
    if(m1 -> magnitude > 100)
    {
        float scalar = 100 / (m1 -> magnitude);
        Vec2_scale(m1, scalar);
        Vec2_scale(m2, scalar);
    }

    if(m2 -> magnitude > 100)
    {
        float scalar = 100 / (m2 -> magnitude);
        Vec2_scale(m1, scalar);
        Vec2_scale(m2, scalar);
    }
}

