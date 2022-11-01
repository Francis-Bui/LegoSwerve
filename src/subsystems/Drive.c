#include "../util/OI.c"
#include "../util/SwerveModule.c"

struct SwerveModule leftModule;
struct SwerveModule rightModule;


double getDistance();

float maxSpeed = 0.0;

void zeroModules()
{
	setAngle(leftModule, 0.0);
	setAngle(rightModule, 0.0);
}

void fullDrive()
{
	setSpeed(leftModule, maxSpeed);
	setSpeed(rightModule, maxSpeed);
}

void driveDist(double angle, double dist)
{
	const double ANGLE_TOL = 2;
	const double DIST_TOL = 5;
	setAngle(leftModule, angle);
	setAngle(rightModule, angle);
	while(fabs(getAngle(leftModule) - angle) < ANGLE_TOL && fabs(getAngle(rightModule) - angle) < ANGLE_TOL)
	{}
	resetEncoders(leftModule);
	resetEncoders(rightModule);
	setSpeed(leftModule, 1);
	setSpeed(rightModule, 1);
	while(fabs(getDistance() - dist) < DIST_TOL)
	{}
	setSpeed(leftModule, 0);
	setSpeed(rightModule, 0);
}

typedef enum DriveStates
{
	MANUAL,
	AUTO,
	IDLE,
} DriveStates;

task Drive()
{
	DriveStates DriveState = IDLE;

	while(true)
		{
		if (getButtonPress(buttonLeft))
			DriveState = AUTO;
		else if (getButtonPress(buttonRight))
			DriveState = MANUAL;

		initModule(leftModule, motorA, motorB);
		initModule(rightModule, motorC, motorD);

		switch(DriveState)
		{
			case AUTO:

				break;

			case IDLE:
				setSpeed(leftModule, 0.0);
				setSpeed(rightModule, 0.0);
				break;
		}
	}
}
