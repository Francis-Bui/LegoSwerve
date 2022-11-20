#include "../subsystems/Robot.c"

Robot Magnemite;



bool getPathStatus()
{
    if (Robot_getFrontDistance(&Magnemite) < 5 || Robot_getBackDistance(&Magnemite) < 5 || time1[T4] > MAX_RUNTIME)
    {
        return false;
    }

    return true;
}
