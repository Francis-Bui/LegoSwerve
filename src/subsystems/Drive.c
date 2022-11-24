#include "../util/SwerveModule.c"
#include "../auto/PathTransformer.c"
#include "../auto/PathWatch.c"
#include "../teleop/OI.c"

#pragma config(Sensor, S2,     ,               sensorEV3_Gyro)
#pragma config(Sensor, S3,     ,               sensorEV3_Ultrasonic)
#pragma config(Sensor, S4,     ,               sensorEV3_Ultrasonic)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

SwerveModule leftModule;
SwerveModule rightModule;

PIDController driveStraightController;

void initializePIDSpeed();
void initializePIDAngle();
void initializePIDStraight();
void resetPIDSpeedControllers();
void resetPIDAngleControllers();
void resetPIDStraight();

void startSpeedPIDTasks();
void stopSpeedPIDTasks();
void startAnglePIDTasks();
void stopAnglePIDTasks();
void stopDriveStraightPID();
void startDriveStraightPID();
void eStop();
void selectPath();
void logMotorData();

void Manual_teleop(bool closedLoop);
void Auto_followPathLinear( const float* distanceArray, const float* headingArray, const float* rpmArray,
							const float* timeArray, const float* rotationArray, const int PATH_LEN);

void Auto_followPathCurve(const float* rpmAlpha, const float* rpmBeta, const float* timeArray, const float* rotationArray, const int PATH_LEN);

typedef enum DriveStates
{
	MANUAL,
	AUTO,
	IDLE,
} DriveStates;

task t_RPID_SpeedOne()
{
	while(true)
	{
		float err = rightModule.targetMotorSpeeds[0] - Swerve_getMotorSpeed(&rightModule, 0);
		float drive = PID_calculateDrive(&(rightModule.ctrlSpeedOne), err);
		setMotorSpeed(rightModule.motorPorts[0], drive);
	}
}

task t_RPID_SpeedTwo()
{
	while(true)
	{
		float err = rightModule.targetMotorSpeeds[1] - Swerve_getMotorSpeed(&rightModule, 1);
		float drive = PID_calculateDrive(&(rightModule.ctrlSpeedTwo), err);
		setMotorSpeed(rightModule.motorPorts[1], drive);
	}
}

task t_LPID_SpeedOne()
{
	while(true)
	{
		float err = leftModule.targetMotorSpeeds[0] - Swerve_getMotorSpeed(&leftModule, 0);
		float drive = PID_calculateDrive(&(leftModule.ctrlSpeedOne), err);
		setMotorSpeed(leftModule.motorPorts[0], drive);
	}
}

task t_LPID_SpeedTwo()
{
	while(true)
	{
		float err = leftModule.targetMotorSpeeds[1] - Swerve_getMotorSpeed(&leftModule, 1);
		float drive = PID_calculateDrive(&(leftModule.ctrlSpeedTwo), err);
		setMotorSpeed(leftModule.motorPorts[1], drive);
	}
}

task t_LPID_AngleOne()
{
	resetMotorEncoder(leftModule.motorPorts[0]);
	while(true)
	{
		float err = leftModule.targetMotorAngles[0] - Swerve_getMotorAngle(&leftModule, 0);
		float drive = PID_calculateDrive(&(leftModule.ctrlAngleOne),err);
		setMotorSpeed(leftModule.motorPorts[0], drive);
	}
}
task t_LPID_AngleTwo()
{
	resetMotorEncoder(leftModule.motorPorts[1]);
	while(true)
	{
		float err = leftModule.targetMotorAngles[1] - Swerve_getMotorAngle(&leftModule, 1);
		float drive = PID_calculateDrive(&(leftModule.ctrlAngleTwo),err);
		setMotorSpeed(leftModule.motorPorts[1], drive);
	}
}

task t_RPID_AngleOne()
{
	resetMotorEncoder(rightModule.motorPorts[0]);
	while(true)
	{
		float err = rightModule.targetMotorAngles[0] - Swerve_getMotorAngle(&rightModule, 0);
		float drive = PID_calculateDrive(&(rightModule.ctrlAngleOne),err);
		setMotorSpeed(rightModule.motorPorts[0], drive);
	}
}
task t_RPID_AngleTwo()
{
	resetMotorEncoder(rightModule.motorPorts[1]);
	while(true)
	{
		float err = rightModule.targetMotorAngles[1] - Swerve_getMotorAngle(&rightModule, 1);
		float drive = PID_calculateDrive(&(rightModule.ctrlAngleTwo),err);
		setMotorSpeed(rightModule.motorPorts[1], drive);
	}
}

task t_DriveStraightPID()
{
	Robot_resetGyro(Magnemite);
	while(true)
	{
		float err = driveStraightController.target - Robot_getRotation(&Magnemite);
		float drive = PID_calculateDrive((&driveStraightController, err));

		Swerve_setDriveSpeed(&leftModule, 50 + drive, 50 + drive);
		Swerve_setDriveSpeed(&rightModule, 50 - drive, 50 - drive);
	}
}

task main()
{
	DriveStates DriveState = AUTO;

	datalogClear();

	Robot_initRobot(&Magnemite, GYRO_PORT, ACCEL_PORT, F_ULTRASONIC_PORT, B_ULTRASONIC_PORT);
	Swerve_initModule(&leftModule, TOP_LEFT_MOTOR, BOT_LEFT_MOTOR);
	Swerve_initModule(&rightModule, TOP_RIGHT_MOTOR, BOT_RIGHT_MOTOR);
	initializePIDSpeed();
	initializePIDAngle();
	initializePIDStraight();


	bool buttonPressed = false;
	while(buttonPressed)
	{
		if (getButtonPress(buttonLeft))
		{
			DriveState = AUTO;
			buttonPressed = false;
		}
		else if (getButtonPress(buttonRight))
		{
			DriveState = MANUAL;
			buttonPressed = false;
		}
		else if (getButtonPress(buttonUp))
		{
			DriveState = IDLE;
			buttonPressed = false;
		}
	}

	switch(DriveState)
	{
		case AUTO:

			resetPIDSpeedControllers();
			Swerve_setMotorTargetSpeed(&rightModule, 0, 170);
			Swerve_setMotorTargetSpeed(&rightModule, 1, 170);
			//Swerve_setMotorTargetSpeed(&leftModule, 0, 100);
			//Swerve_setMotorTargetSpeed(&leftModule, 1, 100);

			startSpeedPIDTasks();

			while (true) {logMotorData();}

			//Auto_followPathLinear(PATH_ONE_DISTANCE, PATH_ONE_HEADING, PATH_ONE_RPM, PATH_ONE_TIME, PATH_ONE_LEN);
			//Auto_followPathCurve(PATH_TWO_RPM_ALPHA, PATH_TWO_RPM_BETA, PATH_TWO_TIME, PATH_TWO_LEN);

			break;

		case IDLE:

			break;

		case MANUAL:

			Manual_teleop(true);

			break;
	}
}

void Auto_followPathLinear(const float* distanceArray, const float* headingArray, const float* rpmArray,
						const float* timeArray,  const float* rotationArray, int PATH_LEN)
{
	time1[T4] = 0;

    for(int i = 0; i < PATH_LEN; i++)
    {
        stopSpeedPIDTasks();
		stopAnglePIDTasks();
		resetPIDAngleControllers();
		resetPIDSpeedControllers();
	    Swerve_setDriveSpeed(&leftModule, 0, 0);
	    Swerve_setDriveSpeed(&rightModule, 0, 0);
		Swerve_resetEncoders(&leftModule);
		Swerve_resetEncoders(&rightModule);

		time1[T3] = 0;
		while(time1[T3] < 300){}

		Swerve_setMotorTargetAngle(&leftModule, 0, headingArray[i]);
		Swerve_setMotorTargetAngle(&leftModule, 1, -headingArray[i]);
		Swerve_setMotorTargetAngle(&rightModule, 0, headingArray[i]);
		Swerve_setMotorTargetAngle(&rightModule, 1, -headingArray[i]);

		startAnglePIDTasks();

		while (
				(int) Swerve_getMotorAngle(&rightModule, 0) != headingArray[i] ||
				(int) Swerve_getMotorAngle(&rightModule, 1) != -headingArray[i] ||
				(int) Swerve_getMotorAngle(&leftModule, 0) != headingArray[i] ||
				(int) Swerve_getMotorAngle(&leftModule, 1) != -headingArray[i]) {}

		stopAnglePIDTasks();
		resetPIDAngleControllers();

		Swerve_resetEncoders(&leftModule);
		Swerve_resetEncoders(&rightModule);

		Swerve_setMotorTargetSpeed(&leftModule, 0, rpmArray[i]);
		Swerve_setMotorTargetSpeed(&leftModule, 1, rpmArray[i]);
		Swerve_setMotorTargetSpeed(&rightModule, 0, rpmArray[i]);
		Swerve_setMotorTargetSpeed(&rightModule, 1, rpmArray[i]);

		startSpeedPIDTasks();

		time1[T3] = 0;

		while  (time1[T3] < timeArray[i] && getPathStatus() == true &&
				Robot_getRotation(&Magnemite) < rotationArray[i] - HEADING_TOL &&
				Robot_getRotation(&Magnemite) > rotationArray + HEADING_TOL){}

		if (getPathStatus() == false || Robot_getRotation(&Magnemite) < rotationArray[i] - HEADING_TOL || Robot_getRotation(&Magnemite) > rotationArray[i] + HEADING_TOL)
			break;
        //while (Swerve_getDist(&rightModule) != distanceArray[i] || Swerve_getDist(&leftModule) != distanceArray[i]){}
	}
	eStop();
}

void Auto_followPathCurve(const float* rpmAlpha, const float* rpmBeta, const float* timeArray, const float* rotationArray, const int* PATH_LEN)
{
	time1[T4] = 0;

    for(int i = 0; i < PATH_LEN; i++)
    {
        stopSpeedPIDTasks();
		resetPIDSpeedControllers();
	    Swerve_setDriveSpeed(&leftModule, 0, 0);
	    Swerve_setDriveSpeed(&rightModule, 0, 0);
		Swerve_resetEncoders(&leftModule);
		Swerve_resetEncoders(&rightModule);

		time1[T3] = 0;
		while(time1[T3] < 300){}


		Swerve_resetEncoders(&leftModule);
		Swerve_resetEncoders(&rightModule);

		Swerve_setMotorTargetSpeed(&leftModule, 0, rpmAlpha[i]);
		Swerve_setMotorTargetSpeed(&leftModule, 1, rpmBeta[i]);
		Swerve_setMotorTargetSpeed(&rightModule, 0, rpmAlpha[i]);
		Swerve_setMotorTargetSpeed(&rightModule, 1, rpmBeta[i]);

		startSpeedPIDTasks();

		time1[T3] = 0;

		while(time1[T3] < timeArray[i] && getPathStatus() == true){}

		if (getPathStatus() == false || Robot_getRotation(&Magnemite) <= rotationArray[i] - HEADING_TOL || Robot_getRotation(&Magnemite) >= rotationArray[i] + HEADING_TOL)
			break;

        //while (Swerve_getDist(&rightModule) != distanceArray[i] || Swerve_getDist(&leftModule) != distanceArray[i]){}
	}
	eStop();
}

void selectPath()
{
	//TODO, alison's function to do
}

void Manual_teleop(bool closedLoop)
{
	stopSpeedPIDTasks();
	stopAnglePIDTasks();
	resetPIDAngleControllers();
	resetPIDSpeedControllers();

	startSpeedPIDTasks();

	while (true)
	{

		short* joystickInput = getJoystickInput();
		short* motorPowers = getMotorPowers(joystickInput[0], joystickInput[1]);

		if (closedLoop == true)
		{
			Swerve_setMotorTargetSpeed(&rightModule, 0, motorPowers[0] * POWER_SCALAR);
			Swerve_setMotorTargetSpeed(&rightModule, 1, motorPowers[1] * POWER_SCALAR);
			Swerve_setMotorTargetSpeed(&leftModule, 0, motorPowers[0] * POWER_SCALAR);
			Swerve_setMotorTargetSpeed(&leftModule, 1, motorPowers[1] * POWER_SCALAR);
		}

		else
		{
			Swerve_setDriveSpeed(&leftModule, motorPowers[0] * POWER_SCALAR, motorPowers[1] * POWER_SCALAR);
			Swerve_setDriveSpeed(&rightModule, motorPowers[0] * POWER_SCALAR, motorPowers[1] * POWER_SCALAR);
		}

	}
}

void startSpeedPIDTasks()
{
	//startTask(t_LPID_SpeedOne);
	//startTask(t_LPID_SpeedTwo);
	startTask(t_RPID_SpeedOne);
	startTask(t_RPID_SpeedTwo);
	startTask(t_LPID_SpeedOne);
	startTask(t_LPID_SpeedTwo);
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
	startTask(t_RPID_AngleOne);
	startTask(t_RPID_AngleTwo);
}

void stopAnglePIDTasks()
{
	stopTask(t_LPID_AngleOne);
	stopTask(t_LPID_AngleTwo);
	stopTask(t_RPID_AngleOne);
	stopTask(t_RPID_AngleTwo);
}

void startDriveStraightPID()
{
	startTask(t_DriveStraightPID);
}

void stopDriveStraightPID()
{
	stopTask(t_DriveStraightPID);
}

void resetPIDSpeedControllers()
{
	PID_reset(&(leftModule.ctrlSpeedOne));
	PID_reset(&(leftModule.ctrlSpeedTwo));
	PID_reset(&(rightModule.ctrlSpeedOne));
	PID_reset(&(rightModule.ctrlSpeedTwo));
}

void resetPIDAngleControllers()
{
	PID_reset(&(leftModule.ctrlAngleOne));
	PID_reset(&(leftModule.ctrlAngleTwo));
	PID_reset(&(rightModule.ctrlAngleOne));
	PID_reset(&(rightModule.ctrlAngleTwo));
}

void resetPIDStraight()
{
	PID_reset(&driveStraightController);
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

void initializePIDStraight()
{
	PID_initPIDConstants(&driveStraightController, STRAIGHT[0], STRAIGHT[1], STRAIGHT[2], STRAIGHT[3]);
	PID_initOutputRange(&driveStraightController, STRAIGHT[4], STRAIGHT[5]);
	PID_reset(&driveStraightController);

	driveStraightController.target = 0;
}

void logMotorData()
{
	datalogAddValueWithTimeStamp(0, Swerve_getMotorSpeed(&leftModule, 0));
	datalogAddValueWithTimeStamp(1, Swerve_getMotorSpeed(&leftModule, 1));
	datalogAddValueWithTimeStamp(2, Swerve_getMotorSpeed(&rightModule, 0));
	datalogAddValueWithTimeStamp(3, Swerve_getMotorSpeed(&rightModule, 1));
	datalogAddValueWithTimeStamp(4, Swerve_getMotorAngle(&leftModule, 0));
	datalogAddValueWithTimeStamp(5, Swerve_getMotorAngle(&leftModule, 1));
	datalogAddValueWithTimeStamp(6, Swerve_getMotorAngle(&rightModule, 0));
	datalogAddValueWithTimeStamp(7, Swerve_getMotorAngle(&rightModule, 1));
}

void eStop()
{
    stopSpeedPIDTasks();
	stopAnglePIDTasks();
	resetPIDAngleControllers();
	resetPIDSpeedControllers();

	Swerve_setDriveSpeed(&leftModule, 0, 0);
	Swerve_setDriveSpeed(&rightModule, 0, 0);
	Swerve_resetEncoders(&leftModule);
	Swerve_resetEncoders(&rightModule);

	Swerve_setMotorTargetAngle(&leftModule, 0, LOCK_ANGLE);
	Swerve_setMotorTargetAngle(&leftModule, 1, -LOCK_ANGLE);
	Swerve_setMotorTargetAngle(&rightModule, 0, -LOCK_ANGLE);
	Swerve_setMotorTargetAngle(&rightModule, 1, LOCK_ANGLE);

	startAnglePIDTasks();

	time1[T3] = 0;
	while(time1[T3] < 3000){}

	stopAnglePIDTasks();
	resetPIDAngleControllers();

	Swerve_resetEncoders(&leftModule);
	Swerve_resetEncoders(&rightModule);

	Swerve_setDriveSpeed(&leftModule, 0, 0);
	Swerve_setDriveSpeed(&rightModule, 0, 0);

	stopAllTasks();

	setMotorBrakeMode(leftModule.motorOneIndex, motorBrake);
	setMotorBrakeMode(leftModule.motorTwoIndex, motorBrake);
	setMotorBrakeMode(rightModule.motorOneIndex, motorBrake);
	setMotorBrakeMode(rightModule.motorTwoIndex, motorBrake);

}
