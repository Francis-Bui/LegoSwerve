typedef struct Robot
{
    tSensors gyroIndex;
    tSensors accelIndex;
    tSensors frontUltrasonicIndex;
    tSensors backUltrasonicIndex;

} Robot;

void Robot_resetGyro(Robot *robot);
void Robot_resetAccel(Robot *robot);

void Robot_initRobot(Robot *robot, tSensors gyroIndexIn, tSensors accelIndexIn, tSensors frontUltrasonicIndexIn, tSensors backUltrasonicIndexIn)
{
    robot -> gyroIndex = gyroIndexIn;
    robot -> accelIndex = accelIndexIn;
    robot -> frontUltrasonicIndex = frontUltrasonicIndexIn;
    robot -> backUltrasonicIndex = backUltrasonicIndexIn;
    Robot_resetGyro(robot);
    //Robot_resetAccel(robot);
}

/**
 * Returns robot rotation in degrees
 * based on last setpoint
 * @param Robot pointer to robot struct
*/
float Robot_getRotation(Robot *robot)
{
    return getGyroDegrees(robot -> gyroIndex);
}

void Robot_resetGyro(Robot *robot)
{
    resetGyro(robot -> gyroIndex);
}

void Robot_resetAccel(Robot *robot)
{
	sensorReset(robot -> accelIndex);
}

float Robot_getFrontDistance(Robot *robot)
{
		//return 50;
    return getUSDistance(robot -> frontUltrasonicIndex);
}

float Robot_getBackDistance(Robot *robot)
{
		//return 50;
    return getUSDistance(robot -> backUltrasonicIndex);
}
