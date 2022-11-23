#include "PID.c"
#include "Kinematics.c"
#include "Constants.c"

typedef struct SwerveModule{
	int motorOneIndex;
	int motorTwoIndex;
	int motorPorts[2];
	
	float targetAngle;
	float targetDriveSpeed;

	float targetMotorSpeeds[2];
	float targetMotorAngles[2];

	float targetAngularSpeed;
	float motorOneSpeed;
	float motorTwoSpeed;
	float currentDriveSpeed;
	float currentAngularSpeed;
	float currentAngle;


	PIDController ctrlSpeedOne;
	PIDController ctrlSpeedTwo;

	PIDController ctrlAngleOne;
	PIDController ctrlAngleTwo;
} SwerveModule;

/*
Reset encoders for swerve
*/
void Swerve_resetEncoders(SwerveModule *swerve)
{
	resetMotorEncoder(swerve -> motorPorts[0]);
	resetMotorEncoder(swerve -> motorPorts[1]);
}

/*
Initialize motors for swerve
*/
void Swerve_initModule(SwerveModule *swerve, int motorOneIndexIn, int motorTwoIndexIn)
{
	swerve -> motorPorts[0] = motorOneIndexIn;
	swerve -> motorPorts[1] = motorTwoIndexIn;

	Swerve_resetEncoders(swerve);
}

/**
 * Sets target speed for PID loop in rpms
*/
void Swerve_setMotorTargetSpeed(SwerveModule *swerve, int motIdx, float target)
{
	swerve -> targetMotorSpeeds[motIdx] = target * 2;
}

/**
 * Sets target angle for specific motor in degrees
*/
void Swerve_setMotorTargetAngle(SwerveModule *swerve, int motIdx, float target)
{
	swerve -> targetMotorAngles[motIdx] = target;
}

void Swerve_setDriveSpeed(SwerveModule *swerve, float motorOneSpeed, float motorTwoSpeed) // set drive speed out of 100%
{
	setMotorSpeed(swerve -> motorPorts[0], motorOneSpeed);
	setMotorSpeed(swerve -> motorPorts[1], motorTwoSpeed);
}

/**
 * Returns speed in milimeteres per second
*/
float Swerve_getSpeed(SwerveModule *swerve) // Returns current swerve module speed in meters per second
{
	swerve -> currentDriveSpeed = ((2 * PI * WHEEL_RADIUS * getMotorRPM(swerve -> motorPorts[0]) * NET_GEAR_RATIO / 60) +
							  (2 * PI * WHEEL_RADIUS * getMotorRPM(swerve -> motorPorts[1]) * NET_GEAR_RATIO / 60));
	return swerve -> currentDriveSpeed;
}

/**
 * Returns motor speed in rpm
*/
float Swerve_getMotorSpeed(SwerveModule *swerve, int motIdx) // Returns meters per second of differential gear
{
	// swerve -> motorOneSpeed = (PI * GEAR_RADIUS * getMotorRPM(swerve -> motorOneIndex) / 60);
	// return swerve -> motorOneSpeed;
	return getMotorRPM(swerve -> motorPorts[motIdx]);
}

/**
 * Returns wheel angles relative to motor
*/
float Swerve_getMotorAngle(SwerveModule *swerve, int motIdx)
{
	//implement angle tracking
	return getMotorEncoder(swerve -> motorPorts[motIdx]) * ENCODER_TO_ANGLE;
}


float Swerve_getDriveSpeed(SwerveModule *swerve)
{
	swerve -> currentDriveSpeed = ((Swerve_getMotorSpeed(swerve,0) - Swerve_getMotorSpeed(swerve,1)) / GEAR_RADIUS) * DIFF_TO_WHEEL * WHEEL_RADIUS;

	return swerve -> currentDriveSpeed;
}

