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

	struct PIDController ctrlOne;
	struct PIDController ctrlTwo;
};

void Swerve_setPower(struct SwerveModule *swerve,float motorOneP, float motorTwoP)
{
	motor[swerve -> motorOneIndex] = motorOneP;
	motor[swerve -> motorTwoIndex] = -motorTwoP;
}

void Swerve_initModule(struct SwerveModule *swerve, int motorOneIndexIn, int motorTwoIndexIn, char gyroIndexIn[3])
{
	swerve -> motorOneIndex = motorOneIndexIn;
	swerve -> motorTwoIndex = motorTwoIndexIn;
	swerve -> gyroIndex = gyroIndexIn[3];
}

void Swerve_setAngle(struct SwerveModule *swerve, float angle)
{
	swerve -> targetAngle = angle;
}

void Swerve_setSpeed(struct SwerveModule *swerve, float speed)
{
	swerve -> targetSpeed = speed;
}

float Swerve_getAngle(struct SwerveModule *swerve)
{
	swerve -> currentAngle = getGyroDegrees(swerve -> gyroIndex);
	return (swerve -> currentAngle);
}

float Swerve_getSpeed(struct SwerveModule *swerve)
{
	//swerve -> currentSpeed = (use kinematics here)
	return swerve -> currentSpeed;
}

float Swerve_getMotorOneSpeed(struct SwerveModule *swerve)
{
	// fill
	return 0;
}

float Swerve_getMotorTwoSpeed(struct SwerveModule *swerve)
{
	//fill
	return 0;
}


void Swerve_resetEncoders(struct SwerveModule *swerve)
{
	resetMotorEncoder(swerve -> motorOneIndex);
	resetMotorEncoder(swerve -> motorTwoIndex);
}
