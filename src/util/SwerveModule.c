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

	struct PIDController controllerOne;
	struct PIDController controllerTwo;
};

void setPower(struct SwerveModule *swerve,float motorOneP, float motorTwoP)
{
	motor[swerve -> motorOneIndex] = motorOneP;
	motor[swerve -> motorTwoIndex] = -motorTwoP;
}

void initModule(struct SwerveModule *swerve, int motorOneIndexIn, int motorTwoIndexIn, char gyroIndexIn[3])
{
	swerve -> motorOneIndex = motorOneIndexIn;
	swerve -> motorTwoIndex = motorTwoIndexIn;
	swerve -> gyroIndex = gyroIndexIn[3];
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
	return swerve -> currentSpeed;
}

void resetEncoders(struct SwerveModule *swerve)
{
	resetMotorEncoder(swerve -> motorOneIndex);
	resetMotorEncoder(swerve -> motorTwoIndex);
}
