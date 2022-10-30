#include "PID.c"

struct SwerveModule{
	int motorOneIndex;
	int motorTwoIndex;
	int gyroIndex;

	float targetSpeed;
	float targetAngle;
	float currentSpeed;
	float currentAngle;

	struct PIDController controllerOne;
	struct PIDController controllerTwo;
};

void setPower(struct SwerveModule *swerve,float motorOneP, float motorTwoP)
{
	motor[swerve -> motorOneIndex] = motorOneP;
	motor[swerve -> motorTwoIndex] = -motorTwoP;
}

void initModule(struct SwerveModule *swerve, int motorOneIndexIn, int motorTwoIndexIn, int gyroIndexIn)
{
	swerve -> motorOneIndex = motorOneIndexIn;
	swerve -> motorTwoIndex = motorTwoIndexIn;
	swerve -> gyroIndex = gyroIndexIn;
}

void setAngle(struct SwerveModule *swerve, float angle)
{
	swerve -> targetAngle = angle;
}

void setSpeed(struct SwerveModule *swerve, float speed)
{
	swerve -> targetSpeed = speed;
}

float getAngle(struct SwerveModule *swerve)
{
	swerve -> currentAngle = getGyroDegrees(swerve -> gyroIndex);
	return (swerve -> currentAngle);
}

float getSpeed(struct SwerveModule *swerve)
{
	//swerve -> currentSpeed = (use kinematics here)
	return swerve -> currentSpeed
}
