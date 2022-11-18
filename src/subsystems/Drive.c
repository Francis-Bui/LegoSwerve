#include "../util/SwerveModule.c"


SwerveModule leftModule;
SwerveModule rightModule;

void Drive_driveDist(SwerveModule *left, SwerveModule *right, float distance, float speed);

void zeroModules()
{
	Swerve_setAngleAbsolute(&leftModule, 0.0);
	Swerve_setAngleAbsolute(&rightModule, 0.0);
}

void fullDrive()
{
}

typedef enum DriveStates
{
	AUTO,
	IDLE,
} DriveStates;

task main()
{
	DriveStates DriveState = IDLE;

	Swerve_initModule(&leftModule, motorA, motorB);
	PID_initPIDConstants(&(leftModule.ctrlOne), L_CTRL_ONE[0], L_CTRL_ONE[1], L_CTRL_ONE[2], L_CTRL_ONE[3]);
	PID_initOutputRange(&(leftModule.ctrlOne), L_CTRL_ONE[4], L_CTRL_ONE[5]);
	PID_reset(&(leftModule.ctrlOne));

	PID_initPIDConstants(&(leftModule.ctrlTwo), L_CTRL_TWO[0], L_CTRL_TWO[1], L_CTRL_TWO[2], L_CTRL_TWO[3]);
	PID_initOutputRange(&(leftModule.ctrlTwo), L_CTRL_TWO[4], L_CTRL_TWO[5]);
	PID_reset(&(leftModule.ctrlTwo));

	Swerve_initModule(&rightModule, motorC, motorD);
	PID_initPIDConstants(&(rightModule.ctrlOne), R_CTRL_ONE[0], R_CTRL_ONE[1], R_CTRL_ONE[2], R_CTRL_ONE[3]);
	PID_initOutputRange(&(leftModule.ctrlOne), R_CTRL_ONE[4], R_CTRL_ONE[5]);
	PID_reset(&(rightModule.ctrlOne));

	PID_initPIDConstants(&(rightModule.ctrlTwo), R_CTRL_TWO[0], R_CTRL_TWO[1], R_CTRL_TWO[2], R_CTRL_TWO[3]);
	PID_initOutputRange(&(rightModule.ctrlTwo), R_CTRL_TWO[4], R_CTRL_TWO[5]);
	PID_reset(&(rightModule.ctrlTwo));


	bool buttonPressed = true;
	while(buttonPressed)
	{
		if (getButtonPress(buttonLeft))
		{
			DriveState = AUTO;
			buttonPressed = false;
		}
		else if (getButtonPress(buttonRight))
		{
			DriveState = IDLE;
			buttonPressed = false;
		}
	}

	bool runDrive = true;

	Drive_driveDist(&leftModule, &rightModule, 500, 100);
	//Swerve_setAngleRelative(&leftModule, 360.0);


	while(runDrive)
	{
		/*switch(DriveState)
		{
			case AUTO:
				motor[motorA] = 10
				motor[motorB] = -5;
				wait1Msec(300);
				runDrive = false;
				break;

			case IDLE:
				break;
		}*/

	}
}

void Drive_driveDist(SwerveModule *left, SwerveModule *right, float distance, float speed)
{
	int direction = (distance >= 0) ? 1 : -1;
	Swerve_resetEncoders(left);
	Swerve_resetEncoders(right);
	//Swerve_setDriveSpeed(swerve, 0.5*direction);
	Swerve_setDriveSpeed(left, speed);
	Swerve_setDriveSpeed(right, speed);
	time1[T2] = 0;
	//while(fabs(Swerve_getDist(left)) < fabs(distance))
	while(time1[T2] < 10000)
	{
		//for debugging
		displayCenteredBigTextLine(0, "Left: %f", Swerve_getDriveSpeed(left));
		displayCenteredBigTextLine(5, "Right: %f", Swerve_getDriveSpeed(right));
	}
	Swerve_setDriveSpeed(left, 0);
	Swerve_setDriveSpeed(right, 0);
}


task t_LPID_ControllerOne()
{
	while(true)
	{
		float err = leftModule.targetDriveSpeed - Swerve_getMotorOneSpeed(&leftModule);
		float drive = PID_calculateDrive(&(leftModule.ctrlOne), err);
	}
}

task t_LPID_ControllerTwo()
{
	while(true)
	{
		float err = leftModule.targetDriveSpeed - Swerve_getMotorTwoSpeed(&leftModule);
		float drive = PID_calculateDrive(&(leftModule.ctrlTwo), err);
	}
}

task t_RPID_ControllerOne()
{
	while(true)
	{
		float err = rightModule.targetDriveSpeed - Swerve_getMotorOneSpeed(&rightModule);
		float drive = PID_calculateDrive(&(rightModule.ctrlOne), err);
	}
}

task t_RPID_ControllerTwo()
{
	while(true)
	{
		float err = rightModule.targetDriveSpeed - Swerve_getMotorTwoSpeed(&rightModule);
		float drive = PID_calculateDrive(&(rightModule.ctrlTwo), err);
	}
}
