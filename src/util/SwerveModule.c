#include "PID.c"

struct SwerveModule{
	int motorOneIndex;
	int motorTwoIndex;

	float targetSpeed;
	float targetAngle;

	struct PIDController controllerOne;
	struct PIDController controllerTwo;
};


void setPower(struct SwerveModule *swerve,float motorOneP, float motorTwoP)
{
	motor[swerve -> motorOneIndex] = motorOneP;
	motor[swerve -> motorTwoIndex] = motorTwoP;
}

void initModule(struct SwerveModule *swerve, int motorOneIndexIn, int motorTwoIndexIn)
{
	swerve -> motorOneIndex = motorOneIndexIn;
	swerve -> motorTwoIndex = motorTwoIndexIn;
}

void setAngle(struct SwerveModule *swerve, float angle)
{
	swerve -> targetAngle = angle;
}

void setSpeed(struct SwerveModule *swerve, float speed)
{
	swerve -> targetSpeed = speed;
}
