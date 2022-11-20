#include "PID.c"
#include "Kinematics.c"

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
	swerve -> targetMotorSpeeds[motIdx] = target;
}

/**
 * Sets target angle for specific motor in degrees
*/
void Swerve_setMotorTargetAngle(SwerveModule *swerve, int motIdx, float target)
{
	swerve -> targetMotorAngles[motIdx] = target;
}

void Swerve_setAngleRelative(SwerveModule *swerve, float angle)
{
	swerve -> targetAngle = angle; // multiply by 2 to account for 1:2 gear ratio
	setMotorSyncEncoder(swerve -> motorPorts[0], swerve -> motorPorts[1], -ANGULAR_SPEED, swerve -> targetAngle, ANGULAR_SPEED);
}

void Swerve_setAngleTarget(SwerveModule *swerve, float target)
{
	swerve -> targetAngle = target * 2.0;
}

void Swerve_setAngleAbsolute(SwerveModule *swerve, float angle)
{
	swerve -> targetAngle = angle; // multiply by 2 to account for 1:2 gear ratio
	setMotorTarget(swerve -> motorPorts[0], swerve -> targetAngle, ANGULAR_SPEED);
	setMotorTarget(swerve -> motorPorts[1], swerve -> targetAngle, -ANGULAR_SPEED);
}

void Swerve_setDriveSpeed(SwerveModule *swerve, float speed) // set drive speed in rpm
{
	swerve -> targetDriveSpeed = POWER_RATE * speed; // convert m/s to power value
	setMotorSpeed(swerve -> motorPorts[0], speed);
	setMotorSpeed(swerve -> motorPorts[1], speed);
}

float Swerve_getAngle(SwerveModule *swerve, int motIdx)
{
	//calc encoder to angle
	return getMotorEncoder(swerve -> motorPorts[motIdx]) * ENCODER_TO_ANGLE;
}

float Swerve_getSpeed(SwerveModule *swerve) // Returns current swerve module speed in meters per second
{
	swerve -> currentDriveSpeed = ((2 * PI * WHEEL_RADIUS * getMotorRPM(swerve -> motorPorts[0]) * NET_GEAR_RATIO / 60) +
							  (2 * PI * WHEEL_RADIUS * getMotorRPM(swerve -> motorPorts[1]) * NET_GEAR_RATIO / 60));
	return swerve -> currentDriveSpeed;
}

//distance in cms

float Swerve_getDistOne(SwerveModule *swerve)
{
	return getMotorEncoder(swerve -> motorPorts[0]) * NET_GEAR_RATIO * 2 * PI * WHEEL_RADIUS;
}

float Swerve_getDistTwo(SwerveModule *swerve)
{
	//multiply by negative one to account for negative encoder counts
	return getMotorEncoder(swerve -> motorPorts[1]) * NET_GEAR_RATIO * 2 * PI * WHEEL_RADIUS;
}

float Swerve_getDist(SwerveModule *swerve)
{
	return Swerve_getDistOne(swerve) + Swerve_getDistTwo(swerve);
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

float Swerve_getMotorAngle(SwerveModule *swerve, int motIdx) // Returns meters per second of differential gear
{
	//implement angle tracking
	return getMotorEncoder(swerve -> motorPorts[motIdx]) * ENCODER_TO_ANGLE;
}


// float Swerve_getAngularSpeed(SwerveModule *swerve)
// {
// 	swerve -> currentAngularSpeed = (-Swerve_getMotorOneSpeed(swerve) + (3 * Swerve_getMotorTwoSpeed(swerve))) / 2;
// 	return swerve -> currentAngularSpeed;
// }

float Swerve_getDriveSpeed(SwerveModule *swerve)
{
	swerve -> currentDriveSpeed = ((Swerve_getMotorSpeed(swerve,0) - Swerve_getMotorSpeed(swerve,1)) / GEAR_RADIUS) * DIFF_TO_WHEEL * WHEEL_RADIUS;

	return swerve -> currentDriveSpeed;
}

// void Swerve_setAngularSpeed(SwerveModule *swerve, float speed)
// {
// 	swerve -> targetAngularSpeed = speed;
// }
