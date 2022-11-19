#include "../util/SwerveModule.c"
#include "../auto/PathTransformer.c"

SwerveModule leftModule;
SwerveModule rightModule;

void Drive_driveDist(SwerveModule *left, SwerveModule *right, float distance, float speed);

void Auto_followPath(const float* distanceArray, const float* headingArray, const float* rpmArray);

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

task t_RPID_ControllerOne()
{
	while(true)
	{
		float err = rightModule.targetMotorOneSpeed - Swerve_getMotorOneSpeed(&rightModule);
		float drive = PID_calculateDrive(&(rightModule.ctrlOne), err);
		setMotorSpeed(rightModule.motorOneIndex, drive);
	}
}

task t_RPID_ControllerTwo()
{
	while(true)
	{
		float err = rightModule.targetMotorTwoSpeed - Swerve_getMotorTwoSpeed(&rightModule);
		float drive = PID_calculateDrive(&(rightModule.ctrlTwo), err);
		setMotorSpeed(rightModule.motorTwoIndex, drive);
	}
}

task t_LPID_ControllerOne()
{
	while(true)
	{
		float err = leftModule.targetMotorOneSpeed - Swerve_getMotorOneSpeed(&leftModule);
		float drive = PID_calculateDrive(&(leftModule.ctrlOne), err);
		setMotorSpeed(leftModule.motorOneIndex, drive);
	}
}

task t_LPID_ControllerTwo()
{
	while(true)
	{
		float err = leftModule.targetMotorTwoSpeed - Swerve_getMotorTwoSpeed(&leftModule);
		float drive = PID_calculateDrive(&(leftModule.ctrlTwo), err);
		setMotorSpeed(leftModule.motorTwoIndex, drive);
	}
}

task t_setLeftModuleAngle()
{
	Swerve_setAngleAbsolute(&leftModule, leftModule.targetAngle);
}

task t_setRightModuleAngle()
{

	Swerve_setAngleAbsolute(&rightModule, rightModule.targetAngle);

}



task main()
{
	DriveStates DriveState = IDLE;

	datalogClear();

	Swerve_initModule(&leftModule, motorA, motorB);
	PID_initPIDConstants(&(leftModule.ctrlOne), L_CTRL_ONE[0], L_CTRL_ONE[1], L_CTRL_ONE[2], L_CTRL_ONE[3]);
	PID_initOutputRange(&(leftModule.ctrlOne), L_CTRL_ONE[4], L_CTRL_ONE[5]);
	PID_reset(&(leftModule.ctrlOne));

	PID_initPIDConstants(&(leftModule.ctrlTwo), L_CTRL_TWO[0], L_CTRL_TWO[1], L_CTRL_TWO[2], L_CTRL_TWO[3]);
	PID_initOutputRange(&(leftModule.ctrlTwo), L_CTRL_TWO[4], L_CTRL_TWO[5]);
	PID_reset(&(leftModule.ctrlTwo));

	Swerve_initModule(&rightModule, motorC, motorD);
	PID_initPIDConstants(&(rightModule.ctrlOne), R_CTRL_ONE[0], R_CTRL_ONE[1], R_CTRL_ONE[2], R_CTRL_ONE[3]);
	PID_initOutputRange(&(rightModule.ctrlOne), R_CTRL_ONE[4], R_CTRL_ONE[5]);
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

	Auto_followPath(PATH_ONE_DISTANCE, PATH_ONE_HEADING, PATH_ONE_RPM);

	/*
	Swerve_setMotOneTarget(&rightModule, 90);
	Swerve_setMotTwoTarget(&rightModule, 90);
	Swerve_setMotOneTarget(&leftModule, 90);
	Swerve_setMotTwoTarget(&leftModule, 90);
	startTask(t_RPID_ControllerOne);
	startTask(t_RPID_ControllerTwo);
	startTask(t_LPID_ControllerOne);
	startTask(t_LPID_ControllerTwo);
	*/

	clearDebugStream();
	while(runDrive)
	{
		if(getAvailSpaceInDebugStream() <= 100)
		{
			clearDebugStream();
		}
		datalogAddValueWithTimeStamp(0, (int)(Swerve_getMotorOneSpeed(&leftModule)));
		datalogAddValueWithTimeStamp(4, (int)(Swerve_getMotorTwoSpeed(&leftModule)));
		//writeDebugStreamLine("Motor one %f, Motor Two %f", Swerve_getMotorOneSpeed(&leftModule), Swerve_getMotorTwoSpeed(&leftModule));
	}
}

void Drive_driveDist(SwerveModule *left, SwerveModule *right, float distance, float speed)
{
	int direction = (distance >= 0) ? 1 : -1;
	/*
	Swerve_resetEncoders(left);
	Swerve_resetEncoders(right);
	//Swerve_setDriveSpeed(swerve, 0.5*direction);
	Swerve_setDriveSpeed(left, speed);
	Swerve_setDriveSpeed(right, speed);
	*/
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

void Auto_followPath(const float* distanceArray, const float* headingArray, const float* rpmArray)
{
    for(int i = 0; i < PATH_LEN; i++)
    {
        stopTask(t_LPID_ControllerOne);
        stopTask(t_LPID_ControllerTwo);
		stopTask(t_RPID_ControllerOne);
        stopTask(t_RPID_ControllerTwo);

	    Swerve_setDriveSpeed(&leftModule, 0);
	    Swerve_setDriveSpeed(&rightModule, 0);
		Swerve_resetEncoders(&leftModule);
		Swerve_resetEncoders(&rightModule);

		time1[T3] = 0;
		while(time1[T3] < 300){}

		Swerve_setAngleTarget(&rightModule, headingArray[i]);
		Swerve_setAngleTarget(&leftModule, headingArray[i]);
		
		startTask(t_setLeftModuleAngle);
		startTask(t_setRightModuleAngle);

		time1[T3] = 0;
		while(time1[T3] < 1300){}

		stopTask(t_setLeftModuleAngle);
		stopTask(t_setRightModuleAngle);

		Swerve_resetEncoders(&leftModule);
		Swerve_resetEncoders(&rightModule);

        //while (Swerve_getAngle(&rightModule) != headingArray[i] || Swerve_getAngle(&leftModule) != headingArray[i]){}

        Swerve_setMotOneTarget(&leftModule, rpmArray[i]);
        Swerve_setMotTwoTarget(&leftModule, rpmArray[i]);
		Swerve_setMotOneTarget(&rightModule, rpmArray[i]);
        Swerve_setMotTwoTarget(&rightModule, rpmArray[i]);

		startTask(t_LPID_ControllerOne);
	    startTask(t_LPID_ControllerTwo);
		startTask(t_RPID_ControllerOne);
	    startTask(t_RPID_ControllerTwo);

		time1[T3] = 0;
		while(time1[T3] < 3000){}
        //while (Swerve_getDist(&rightModule) != distanceArray[i] || Swerve_getDist(&leftModule) != distanceArray[i]){}
	}
	stopTask(t_LPID_ControllerOne);
    stopTask(t_LPID_ControllerTwo);
	stopTask(t_RPID_ControllerOne);
    stopTask(t_RPID_ControllerTwo);

	Swerve_setDriveSpeed(&leftModule, 0);
	Swerve_setDriveSpeed(&rightModule, 0);
	Swerve_resetEncoders(&leftModule);
	Swerve_resetEncoders(&rightModule);
}
