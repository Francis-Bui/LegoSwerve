typedef struct Robot
{
    int gyroIndex;
    int accelIndex;

} Robot;

void Robot_initRobot(Robot *robot, int gyroIndexIn, int accelIndexIn)
{
    robot -> gyroIndex = gyroIndexIn;
    robot -> accelIndex = accelIndexIn;
    Robot_resetGyro(robot);
    Robot_resetAccel(robot);
}

/**
 * Returns robot rotation in degrees
 * based on last setpoint
 * @param Robot pointer to robot struct
*/
void Robot_getRotation(Robot *robot)
{
    return getGyroDegrees(robot -> gyroIndex);
}

void Robot_resetGyro(Robot *robot)
{
    resetGyro(robot -> gyroIndex);
    Robot_getHeading(robot);
}

void Robot_resetAccel(Robot *robot)
{

}