#include "../util/SwerveModule.c"
#include "../auto/PathTransformer.c"

SwerveModule leftModule;
SwerveModule rightModule;

void initializePIDSpeed();
void initializePIDAngle();

void startSpeedPIDTasks();
void stopSpeedPIDTasks();
void startAnglePIDTasks();
void stopAnglePIDTasks();

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

task t_RPID_SpeedOne()
{
	while(true)
	{
		float err = rightModule.targetMotorSpeeds[0] - Swerve_getMotorSpeed(&rightModule,0);
		float drive = PID_calculateDrive(&(rightModule.ctrlSpeedOne), err);
		setMotorSpeed(rightModule.motorPorts[0], drive);
	}
}

task t_RPID_SpeedTwo()
{
	while(true)
	{
		float err = rightModule.targetMotorSpeeds[1] - Swerve_getMotorSpeed(&rightModule,1);
		float drive = PID_calculateDrive(&(rightModule.ctrlSpeedTwo), err);
		setMotorSpeed(rightModule.motorPorts[1], drive);
	}
}

task t_LPID_SpeedOne()
{
	while(true)
	{
		float err = leftModule.targetMotorSpeeds[0] - Swerve_getMotorSpeed(&leftModule,0);
		float drive = PID_calculateDrive(&(leftModule.ctrlSpeedOne), err);
		setMotorSpeed(leftModule.motorPorts[0], drive);
	}
}

task t_LPID_SpeedTwo()
{
	while(true)
	{
		float err = leftModule.targetMotorSpeeds[1] - Swerve_getMotorSpeed(&leftModule,1);
		float drive = PID_calculateDrive(&(leftModule.ctrlSpeedTwo), err);
		setMotorSpeed(leftModule.motorPorts[1], drive);
	}
}

task t_LPID_AngleOne()
{
	while(true)
	{
		float err = leftModule.targetMotorAngles[0] - Swerve_getMotorAngle(&leftModule, 0);
		float drive = PID_calculateDrive(&(leftModule.ctrlAngleOne),err);
		setMotorSpeed(leftModule.motorPorts[0], drive);
	}
}
task t_LPID_AngleTwo()
{
	while(true)
	{
		float err = -leftModule.targetMotorAngles[1] - Swerve_getMotorAngle(&leftModule, 1);
		float drive = PID_calculateDrive(&(leftModule.ctrlAngleTwo),err);
		setMotorSpeed(leftModule.motorPorts[1], -drive);
	}
}

task t_RPID_AngleOne()
{
	while(true)
	{
		float err = rightModule.targetMotorAngles[0] - Swerve_getMotorAngle(&rightModule, 0);
		float drive = PID_calculateDrive(&(rightModule.ctrlAngleOne),err);
		setMotorSpeed(rightModule.motorPorts[0], drive);
	}
}
task t_RPID_AngleTwo()
{
	while(true)
	{
		float err = rightModule.targetMotorAngles[1] - Swerve_getMotorAngle(&rightModule, 1);
		float drive = PID_calculateDrive(&(rightModule.ctrlAngleTwo),err);
		setMotorSpeed(rightModule.motorPorts[1], -drive);
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
	Swerve_initModule(&rightModule, motorC, motorD);
	initializePIDSpeed();
	initializePIDAngle();


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

	//Auto_followPath(PATH_ONE_DISTANCE, PATH_ONE_HEADING, PATH_ONE_RPM);

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

	Swerve_setMotorTargetAngle(&leftModule, 0, 90);
	Swerve_setMotorTargetAngle(&leftModule, 1, 90);
	startAnglePIDTasks();

	clearDebugStream();
	while(runDrive)
	{
		// if(getAvailSpaceInDebugStream() <= 100)
		// {
		// 	clearDebugStream();
		// }
		datalogAddValueWithTimeStamp(0, (int) Swerve_getMotorAngle(&leftModule, 0));
		datalogAddValueWithTimeStamp(4, (int) Swerve_getMotorAngle(&leftModule, 1));
		//writeDebugStreamLine("Motor one %f, Motor Two %f", Swerve_getMotorOneSpeed(&leftModule), Swerve_getMotorTwoSpeed(&leftModule));
	}
}

void Auto_followPath(const float* distanceArray, const float* headingArray, const float* rpmArray)
{
    for(int i = 0; i < PATH_LEN; i++)
    {
        stopSpeedPIDTasks();
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

		Swerve_setMotorTargetSpeed(&leftModule, 0, rpmArray[i]);
		Swerve_setMotorTargetSpeed(&leftModule, 1, rpmArray[i]);
		Swerve_setMotorTargetSpeed(&rightModule, 0, rpmArray[i]);
		Swerve_setMotorTargetSpeed(&rightModule, 1, rpmArray[i]);

		startSpeedPIDTasks();

		time1[T3] = 0;
		while(time1[T3] < 3000){}
        //while (Swerve_getDist(&rightModule) != distanceArray[i] || Swerve_getDist(&leftModule) != distanceArray[i]){}
	}
	stopSpeedPIDTasks();

	Swerve_setDriveSpeed(&leftModule, 0);
	Swerve_setDriveSpeed(&rightModule, 0);
	Swerve_resetEncoders(&leftModule);
	Swerve_resetEncoders(&rightModule);
}

void startSpeedPIDTasks()
{
	startTask(t_LPID_SpeedOne);
	startTask(t_LPID_SpeedTwo);
	startTask(t_RPID_SpeedOne);
	startTask(t_RPID_SpeedTwo);
}

void stopSpeedPIDTasks()
{
	stopTask(t_LPID_SpeedOne);
    stopTask(t_LPID_SpeedTwo);
	stopTask(t_RPID_SpeedOne);
    stopTask(t_RPID_SpeedTwo);
}

void startAnglePIDTasks()
{
	startTask(t_LPID_AngleOne);
	startTask(t_LPID_AngleTwo);
}

void stopAnglePIDTasks()
{
	stopTask(t_LPID_AngleOne);
	stopTask(t_LPID_AngleTwo);
}

void initializePIDSpeed()
{
	PID_initPIDConstants(&(leftModule.ctrlSpeedOne), L_SPEED_ONE[0], L_SPEED_ONE[1], L_SPEED_ONE[2], L_SPEED_ONE[3]);
	PID_initOutputRange(&(leftModule.ctrlSpeedOne), L_SPEED_ONE[4], L_SPEED_ONE[5]);
	PID_reset(&(leftModule.ctrlSpeedOne));

	PID_initPIDConstants(&(leftModule.ctrlSpeedTwo), L_SPEED_TWO[0], L_SPEED_TWO[1], L_SPEED_TWO[2], L_SPEED_TWO[3]);
	PID_initOutputRange(&(leftModule.ctrlSpeedTwo), L_SPEED_TWO[4], L_SPEED_TWO[5]);
	PID_reset(&(leftModule.ctrlSpeedTwo));

	PID_initPIDConstants(&(rightModule.ctrlSpeedOne), R_SPEED_ONE[0], R_SPEED_ONE[1], R_SPEED_ONE[2], R_SPEED_ONE[3]);
	PID_initOutputRange(&(rightModule.ctrlSpeedOne), R_SPEED_ONE[4], R_SPEED_ONE[5]);
	PID_reset(&(rightModule.ctrlSpeedOne));

	PID_initPIDConstants(&(rightModule.ctrlSpeedTwo), R_SPEED_TWO[0], R_SPEED_TWO[1], R_SPEED_TWO[2], R_SPEED_TWO[3]);
	PID_initOutputRange(&(rightModule.ctrlSpeedTwo), R_SPEED_TWO[4], R_SPEED_TWO[5]);
	PID_reset(&(rightModule.ctrlSpeedTwo));
}

void initializePIDAngle()
{
	PID_initPIDConstants(&(leftModule.ctrlAngleOne), L_ANGLE_ONE[0], L_ANGLE_ONE[1], L_ANGLE_ONE[2], L_ANGLE_ONE[3]);
	PID_initOutputRange(&(leftModule.ctrlAngleOne), L_ANGLE_ONE[4], L_ANGLE_ONE[5]);
	PID_reset(&(leftModule.ctrlAngleOne));

	PID_initPIDConstants(&(leftModule.ctrlAngleTwo), L_ANGLE_TWO[0], L_ANGLE_TWO[1], L_ANGLE_TWO[2], L_ANGLE_TWO[3]);
	PID_initOutputRange(&(leftModule.ctrlAngleTwo), L_ANGLE_TWO[4], L_ANGLE_TWO[5]);
	PID_reset(&(leftModule.ctrlAngleTwo));

	PID_initPIDConstants(&(rightModule.ctrlAngleOne), R_ANGLE_ONE[0], R_ANGLE_ONE[1], R_ANGLE_ONE[2], R_ANGLE_ONE[3]);
	PID_initOutputRange(&(rightModule.ctrlAngleOne), R_ANGLE_ONE[4], R_ANGLE_ONE[5]);
	PID_reset(&(rightModule.ctrlAngleOne));

	PID_initPIDConstants(&(rightModule.ctrlAngleTwo), R_ANGLE_TWO[0], R_ANGLE_TWO[1], R_ANGLE_TWO[2], R_ANGLE_TWO[3]);
	PID_initOutputRange(&(rightModule.ctrlAngleTwo), R_ANGLE_TWO[4], R_ANGLE_TWO[5]);
	PID_reset(&(rightModule.ctrlAngleTwo));
}
