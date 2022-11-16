#include "PID.c"
#include "Kinematics.c"

typedef struct SwerveModule{
	int motorOneIndex;
	int motorTwoIndex;

	float targetSpeed;
	float targetAngle;
	float currentSpeed;
	float currentAngle;

	PIDController ctrlOne;
	PIDController ctrlTwo;
} SwerveModule;



void Swerve_setPower(SwerveModule *swerve,float motorOneP, float motorTwoP)
{
	motor[swerve -> motorOneIndex] = motorOneP;
	motor[swerve -> motorTwoIndex] = -motorTwoP;
}

void Swerve_initModule(SwerveModule *swerve, int motorOneIndexIn, int motorTwoIndexIn)
{
	swerve -> motorOneIndex = motorOneIndexIn;
	swerve -> motorTwoIndex = motorTwoIndexIn;
}

void Swerve_setAngle(SwerveModule *swerve, float angle)
{
	swerve -> targetAngle = angle;
}

void Swerve_setSpeed(SwerveModule *swerve, float speed)
{
	swerve -> targetSpeed = speed;
}


float Swerve_getSpeed(SwerveModule *swerve)
{
	//swerve -> currentSpeed = (use kinematics here)
	return swerve -> currentSpeed;
}

float Swerve_getMotorOneSpeed(SwerveModule *swerve)
{
	// fill
	return 0;
}

float Swerve_getMotorTwoSpeed(SwerveModule *swerve)
{
	//fill
	return 0;
}


void Swerve_resetEncoders(SwerveModule *swerve)
{
	resetMotorEncoder(swerve -> motorOneIndex);
	resetMotorEncoder(swerve -> motorTwoIndex);
}
