#include "PID.c"
#include "Kinematics.c"

struct SwerveModule{
	int motorOneIndex;
	int motorTwoIndex;
	char gyroIndex;

	float targetSpeed;
	float targetAngle;
	float currentSpeed;
	float currentAngle;

	PIDController ctrlOne;
	PIDController ctrlTwo;
};

typedef struct SwerveModule SwerveModule;


void Swerve_setPower(SwerveModule *swerve,float motorOneP, float motorTwoP)
{
	motor[swerve -> motorOneIndex] = motorOneP;
	motor[swerve -> motorTwoIndex] = -motorTwoP;
}

void Swerve_initModule(SwerveModule *swerve, int motorOneIndexIn, int motorTwoIndexIn, char gyroIndexIn[3])
{
	swerve -> motorOneIndex = motorOneIndexIn;
	swerve -> motorTwoIndex = motorTwoIndexIn;
	swerve -> gyroIndex = gyroIndexIn[3];
}

void Swerve_setAngle(SwerveModule *swerve, float angle)
{
	swerve -> targetAngle = angle;
}

void Swerve_setSpeed(SwerveModule *swerve, float speed)
{
	swerve -> targetSpeed = speed;
}

float Swerve_getAngle(SwerveModule *swerve)
{
	swerve -> currentAngle = getGyroDegrees(swerve -> gyroIndex);
	return (swerve -> currentAngle);
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
