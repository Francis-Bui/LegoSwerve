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

void Robot_resetGyro(Robot *robot)
{
    resetGyro(robot -> gyroIndex);
}

void Robot_resetAccel(Robot *robot)
{

}