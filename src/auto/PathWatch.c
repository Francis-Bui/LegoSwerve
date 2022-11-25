#include "../subsystems/Robot.c"

Robot Magnemite;
const int MAX_RUNTIME = 35000;
const int SAFETY_TOL = 10;
bool getPathStatus()
{
    if (Robot_getFrontDistance(&Magnemite) < SAFETY_TOL || Robot_getBackDistance(&Magnemite) < SAFETY_TOL || time1[T4] > MAX_RUNTIME)
    {
        return false;
    }

    return true;
}
