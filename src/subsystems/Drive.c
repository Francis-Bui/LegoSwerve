#include "../util/OI.c"
#include "../util/SwerveModule.c"

struct SwerveModule leftModule;
struct SwerveModule rightModule;

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

task main()
{
	initModule(leftModule, motorA, motorB);
	initModule(rightModule, motorC, motorD);

	typedef enum DriveState
	{
		MANUAL,
		AUTO,
		IDLE,
	} DriveState;

	switch(DriveState)
	{
		case MANUAL: //TODO: Determine whether or not we need to use PID for manual drive or raw

		switch(getIRState())
		{
			case nonePressed:
				setSpeed(leftModule, 0.0);
				setSpeed(rightModule, 0.0);
				break;

			case forwardLeft:
				setAngle(leftModule, -45.0);
				setAngle(rightModule, -45.0);
				fullDrive();
				break;

			case forwardRight:
				setAngle(leftModule, 45.0);
				setAngle(rightModule, 45.0);
				fullDrive();
				break;

			case forwardFull:
				zeroModules();
				fullDrive();
				break;

			case backLeft:
				setAngle(leftModule, -135.0);
				setAngle(rightModule, -135.0);
				fullDrive();
				break;

			case backRight:
				setAngle(leftModule, 135.0);
				setAngle(rightModule, 135.0);
				fullDrive();
				break;

			case backFull:
				setAngle(leftModule, 180.0);
				setAngle(rightModule, 180.0);
				fullDrive();
				break;

			case spinRight:
				zeroModules();
				setSpeed(leftModule, maxSpeed);
				setSpeed(rightModule, -maxSpeed);
				break;

			case spinLeft:
				zeroModules();
				setSpeed(leftModule, -maxSpeed);
				setSpeed(rightModule, maxSpeed);
				break;

			case leftFull:
				setAngle(leftModule, -90.0);
				setAngle(rightModule, -90.0);
				fullDrive();
				break;

			case rightFull:
				setAngle(leftModule, 90.0);
				setAngle(rightModule, 90.0);
				fullDrive();
				break;
		}
			break;

		case AUTO:

			break;

		case IDLE:
			setSpeed(leftModule, 0.0);
			setSpeed(rightModule, 0.0);
			break;
	}
}
