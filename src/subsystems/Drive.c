#include "../util/SwerveModule.c"
#include "../util/PID.c"
#include "../util/Constants.c"

struct SwerveModule leftModule;
struct SwerveModule rightModule;

double getDistance();

void zeroModules()
{
	setAngle(&leftModule, 0.0);
	setAngle(&rightModule, 0.0);
}

void fullDrive()
{
	setSpeed(&leftModule, MAX_SPEED);
	setSpeed(&rightModule, MAX_SPEED);
}

void driveDist(double angle, double dist)
{
	setAngle(&leftModule, angle);
	setAngle(&rightModule, angle);
	while(fabs(getAngle(&leftModule) - angle) < ANGLE_TOL && fabs(getAngle(&rightModule) - angle) < ANGLE_TOL)
	{}
	resetEncoders(&leftModule);
	resetEncoders(&rightModule);
	setSpeed(&leftModule, 1);
	setSpeed(&rightModule, 1);
	while(fabs(getDistance() - dist) < DIST_TOL)
	{}
	setSpeed(&leftModule, 0);
	setSpeed(&rightModule, 0);
}

typedef enum DriveStates
{
	AUTO,
	IDLE,
} DriveStates;

task Drive()
{
	DriveStates DriveState = IDLE;

	initModule(&leftModule, motorA, motorB, GYROPORT_L);
	initPIDConstants(&(leftModule.ctrlOne), L_CTRL_ONE[0], L_CTRL_ONE[1], L_CTRL_ONE[2], L_CTRL_ONE[3]);
	initOutputRange(&(leftModule.ctrlOne), L_CTRL_ONE[4], L_CTRL_ONE[5]);
	PID_reset(&(leftModule.ctrlOne));
	
	initPIDConstants(&(leftModule.ctrlTwo), L_CTRL_TWO[0], L_CTRL_TWO[1], L_CTRL_TWO[2], L_CTRL_TWO[3]);
	initOutputRange(&(leftModule.ctrlTwo), L_CTRL_TWO[4], L_CTRL_TWO[5]);
	PID_reset(&(leftModule.ctrlTwo));

	initModule(&rightModule, motorC, motorD, GYROPORT_R);
	initPIDConstants(&(rightModule.ctrlOne), R_CTRL_ONE[0], R_CTRL_ONE[1], R_CTRL_ONE[2], R_CTRL_ONE[3]);
	initOutputRange(&(leftModule.ctrlOne), R_CTRL_ONE[4], R_CTRL_ONE[5]);
	PID_reset(&(rightModule.ctrlOne));
	
	initPIDConstants(&(rightModule.ctrlTwo), R_CTRL_TWO[0], R_CTRL_TWO[1], R_CTRL_TWO[2], R_CTRL_TWO[3]);
	initOutputRange(&(rightModule.ctrlTwo), R_CTRL_TWO[4], R_CTRL_TWO[5]);
	PID_reset(&(rightModule.ctrlTwo));

	while(true)
		{
		if (getButtonPress(buttonLeft))
			DriveState = AUTO;
		else if (getButtonPress(buttonRight))
			DriveState = IDLE;


		switch(DriveState)
		{
			case AUTO:

				break;

			case IDLE:
				setSpeed(&leftModule, 0.0);
				setSpeed(&rightModule, 0.0);
				break;
		}
	}
}

task t_LPID_ControllerOne()
{
	while(true)
	{
		float err = leftModule.targetSpeed - getMotorOneSpeed(&leftModule);
		float drive = PID_calculateDrive(&(leftModule.ctrlOne), err);
	}
}

task t_LPID_ControllerTwo()
{
	while(true)
	{
		float err = leftModule.targetSpeed - getMotorTwoSpeed(&leftModule);
		float drive = PID_calculateDrive(&(leftModule.ctrlTwo), err);
	}
}

task t_RPID_ControllerOne()
{
	while(true)
	{
		float err = rightModule.targetSpeed - getMotorOneSpeed(&rightModule);
		float drive = PID_calculateDrive(&(rightModule.ctrlOne), err);
	}
}

task t_RPID_ControllerTwo()
{
	while(true)
	{
		float err = rightModule.targetSpeed - getMotorTwoSpeed(&rightModule);
		float drive = PID_calculateDrive(&(rightModule.ctrlTwo), err);
	}
}

