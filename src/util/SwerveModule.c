#include "PID.c"
#include "Kinematics.c"

typedef struct SwerveModule{
	int motorOneIndex;
	int motorTwoIndex;

	
	float targetAngle;
	float targetDriveSpeed;
	float targetAngularSpeed;
	float motorOneSpeed;
	float motorTwoSpeed;
	float currentDriveSpeed;
	float currentAngularSpeed;
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

void Swerve_setDriveSpeed(SwerveModule *swerve, float speed)
{
	swerve -> targetDriveSpeed = speed;
}

void Swerve_setAngularSpeed(SwerveModule *swerve, float speed)
{
	swerve -> targetAngularSpeed = speed;
}


float Swerve_getSpeed(SwerveModule *swerve) // Returns current swerve module speed in meters per second
{
	swerve -> currentDriveSpeed = ((2 * PI * WHEEL_RADIUS * getMotorRPM(swerve -> motorOneIndex) * NET_GEAR_RATIO / 60) + 
							  (2 * PI * WHEEL_RADIUS * getMotorRPM(swerve -> motorTwoIndex) * NET_GEAR_RATIO / 60));
	return swerve -> currentDriveSpeed;
}

float Swerve_getMotorOneSpeed(SwerveModule *swerve) // Returns meters per second of differential gear
{
	swerve -> motorOneSpeed = (PI * GEAR_RADIUS * getMotorRPM(swerve -> motorOneIndex) / 60); 
	return swerve -> motorOneSpeed;
}

float Swerve_getMotorTwoSpeed(SwerveModule *swerve)
{
	swerve -> motorTwoSpeed = (PI * GEAR_RADIUS * getMotorRPM(swerve -> motorTwoIndex) / 60);
	return swerve -> motorTwoSpeed;
}

float Swerve_getAngularSpeed(SwerveModule *swerve)
{
	swerve -> currentAngularSpeed = (-Swerve_getMotorOneSpeed(swerve) + (3 * Swerve_getMotorTwoSpeed(swerve))) / 2;
	return swerve -> currentAngularSpeed;
}

float Swerve_getDriveSpeed(SwerveModule *swerve)
{
	swerve -> currentDriveSpeed = ((Swerve_getMotorOneSpeed(swerve) - Swerve_getMotorTwoSpeed(swerve)) / GEAR_RADIUS) * DIFF_TO_WHEEL * WHEEL_RADIUS;

	return swerve -> currentDriveSpeed;
}
void Swerve_resetEncoders(SwerveModule *swerve)
{
	resetMotorEncoder(swerve -> motorOneIndex);
	resetMotorEncoder(swerve -> motorTwoIndex);
}
