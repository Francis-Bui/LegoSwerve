#include "../subsystems/Robot.c"

Robot Magnemite;

bool getPathStatus()
{
    if (Robot_getFrontDistance(&Magnemite) < SAFETY_TOL || Robot_getBackDistance(&Magnemite) < SAFETY_TOL || time1[T4] > MAX_RUNTIME)
    {
        return false;
    }

    return true;
}
