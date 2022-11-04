#include "../util/SwerveModule.c"
#include "../util/PID.c"
#include "../util/Constants.c"

struct SwerveModule leftModule;
struct SwerveModule rightModule;

double getDistance();

void zeroModules()
{
	Swerve_setAngle(&leftModule, 0.0);
	Swerve_setAngle(&rightModule, 0.0);
}

void fullDrive()
{
	Swerve_setSpeed(&leftModule, MAX_SPEED);
	Swerve_setSpeed(&rightModule, MAX_SPEED);
}

void driveDist(double angle, double dist)
{
	Swerve_setAngle(&leftModule, angle);
	Swerve_setAngle(&rightModule, angle);
	while(fabs(Swerve_getAngle(&leftModule) - angle) < ANGLE_TOL && fabs(Swerve_getAngle(&rightModule) - angle) < ANGLE_TOL)
	{}
	Swerve_resetEncoders(&leftModule);
	Swerve_resetEncoders(&rightModule);
	Swerve_setSpeed(&leftModule, 1);
	Swerve_setSpeed(&rightModule, 1);
	while(fabs(getDistance() - dist) < DIST_TOL)
	{}
	Swerve_setSpeed(&leftModule, 0);
	Swerve_setSpeed(&rightModule, 0);
}

typedef enum DriveStates
{
	AUTO,
	IDLE,
} DriveStates;

task Drive()
{
	DriveStates DriveState = IDLE;

	Swerve_initModule(&leftModule, motorA, motorB, GYROPORT_L);
	PID_initPIDConstants(&(leftModule.ctrlOne), L_CTRL_ONE[0], L_CTRL_ONE[1], L_CTRL_ONE[2], L_CTRL_ONE[3]);
	PID_initOutputRange(&(leftModule.ctrlOne), L_CTRL_ONE[4], L_CTRL_ONE[5]);
	PID_reset(&(leftModule.ctrlOne));
	
	PID_initPIDConstants(&(leftModule.ctrlTwo), L_CTRL_TWO[0], L_CTRL_TWO[1], L_CTRL_TWO[2], L_CTRL_TWO[3]);
	PID_initOutputRange(&(leftModule.ctrlTwo), L_CTRL_TWO[4], L_CTRL_TWO[5]);
	PID_reset(&(leftModule.ctrlTwo));

	Swerve_initModule(&rightModule, motorC, motorD, GYROPORT_R);
	PID_initPIDConstants(&(rightModule.ctrlOne), R_CTRL_ONE[0], R_CTRL_ONE[1], R_CTRL_ONE[2], R_CTRL_ONE[3]);
	PID_initOutputRange(&(leftModule.ctrlOne), R_CTRL_ONE[4], R_CTRL_ONE[5]);
	PID_reset(&(rightModule.ctrlOne));
	
	PID_initPIDConstants(&(rightModule.ctrlTwo), R_CTRL_TWO[0], R_CTRL_TWO[1], R_CTRL_TWO[2], R_CTRL_TWO[3]);
	PID_initOutputRange(&(rightModule.ctrlTwo), R_CTRL_TWO[4], R_CTRL_TWO[5]);
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
				Swerve_setSpeed(&leftModule, 0.0);
				Swerve_setSpeed(&rightModule, 0.0);
				break;
		}
	}
}

task t_LPID_ControllerOne()
{
	while(true)
	{
		float err = leftModule.targetSpeed - Swerve_getMotorOneSpeed(&leftModule);
		float drive = PID_calculateDrive(&(leftModule.ctrlOne), err);
	}
}

task t_LPID_ControllerTwo()
{
	while(true)
	{
		float err = leftModule.targetSpeed - Swerve_getMotorTwoSpeed(&leftModule);
		float drive = PID_calculateDrive(&(leftModule.ctrlTwo), err);
	}
}

task t_RPID_ControllerOne()
{
	while(true)
	{
		float err = rightModule.targetSpeed - Swerve_getMotorOneSpeed(&rightModule);
		float drive = PID_calculateDrive(&(rightModule.ctrlOne), err);
	}
}

task t_RPID_ControllerTwo()
{
	while(true)
	{
		float err = rightModule.targetSpeed - Swerve_getMotorTwoSpeed(&rightModule);
		float drive = PID_calculateDrive(&(rightModule.ctrlTwo), err);
	}
}

