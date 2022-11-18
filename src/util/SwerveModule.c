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

void Swerve_resetEncoders(SwerveModule *swerve)
{
	resetMotorEncoder(swerve -> motorOneIndex);
	resetMotorEncoder(swerve -> motorTwoIndex);
}

void Swerve_initModule(SwerveModule *swerve, int motorOneIndexIn, int motorTwoIndexIn)
{
	swerve -> motorOneIndex = motorOneIndexIn;
	swerve -> motorTwoIndex = motorTwoIndexIn;
	Swerve_resetEncoders(swerve);
}

void Swerve_setPower(SwerveModule *swerve,float motorOneP, float motorTwoP)
{
	motor[swerve -> motorOneIndex] = motorOneP;
	motor[swerve -> motorTwoIndex] = -motorTwoP;
}

void Swerve_setAngleRelative(SwerveModule *swerve, float angle)
{
	swerve -> targetAngle = angle * 2.0; // multiply by 2 to account for 1:2 gear ratio

	setMotorSyncEncoder(swerve -> motorOneIndex, swerve -> motorTwoIndex, -ANGULAR_SPEED, swerve -> targetAngle, ANGULAR_SPEED);
}

void Swerve_setAngleAbsolute(SwerveModule *swerve, float angle)
{
	swerve -> targetAngle = angle * 2.0; // multiply by 2 to account for 1:2 gear ratio

	setMotorTarget(swerve -> motorOneIndex, swerve -> targetAngle, ANGULAR_SPEED);
	setMotorTarget(swerve -> motorTwoIndex, swerve -> targetAngle, -ANGULAR_SPEED);
}

void Swerve_setDriveSpeed(SwerveModule *swerve, float speed) // set drive speed in rpm
{
	swerve -> targetDriveSpeed = POWER_RATE * speed; // convert m/s to power value
	setMotorSpeed(swerve -> motorOneIndex, speed);
	setMotorSpeed(swerve -> motorTwoIndex, speed);
}

float Swerve_getAngle(SwerveModule *swerve)
{
	swerve -> currentAngle = (getMotorEncoder(swerve -> motorOneIndex)/ 2.0 - getMotorEncoder(swerve -> motorTwoIndex) / 2.0) / 2.0;
	return swerve -> currentAngle;
}

float Swerve_getSpeed(SwerveModule *swerve) // Returns current swerve module speed in meters per second
{
	swerve -> currentDriveSpeed = ((2 * PI * WHEEL_RADIUS * getMotorRPM(swerve -> motorOneIndex) * NET_GEAR_RATIO / 60) +
							  (2 * PI * WHEEL_RADIUS * getMotorRPM(swerve -> motorTwoIndex) * NET_GEAR_RATIO / 60));
	return swerve -> currentDriveSpeed;
}

//distance in cms

float Swerve_getDistOne(SwerveModule *swerve)
{
	return getMotorEncoder(swerve -> motorOneIndex) * NET_GEAR_RATIO * 2 * PI * WHEEL_RADIUS / 10.0;
}

float Swerve_getDistTwo(SwerveModule *swerve)
{
	//multiply by negative one to account for negative encoder counts
	return getMotorEncoder(swerve -> motorTwoIndex) * NET_GEAR_RATIO * 2 * PI * WHEEL_RADIUS / 10.0 *-1;
}

float Swerve_getDist(SwerveModule *swerve)
{
	return Swerve_getDistOne(swerve) + Swerve_getDistTwo(swerve);
}


// code for when we do full kinematics base swerve

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

void Swerve_setAngularSpeed(SwerveModule *swerve, float speed)
{
	swerve -> targetAngularSpeed = speed;
}
