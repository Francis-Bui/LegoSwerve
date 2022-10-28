#include "PID.c"



struct SwerveModule{
	int motorOneIndex;
	int motorTwoIndex;

	float targetSpeed;
	float targetAngle;

	struct PIDController controllerOne;
	struct PIDController controllerTwo;
}

void initModule(struct SwerveModule *swerve);
void setAngle(struct SwerveModule *swerve, float angle);
void setSpeed(struct SwerveModule *swerve, float speed);

void setPower(struct SwerveModule *swerve,float motorOneP, float motorTwoP)
{
	motor[swerve -> motorOneIndex] = motorOneP;
	motor[swerve -> motorTwoIndex] = motorTwoP;
}

void initModule(struct SwerveModule *swerve)
{}

void setAngle(struct SwerveModule *swerve, float angle)
{}

void setSpeed(struct SwerveModule *swerve, float speed)
{}
