#include "PathTransformer.c"

void followPath(float pathArray[PATH_LEN][PATH_HEIGHT])
{
    for(int i = 0; i < PATH_LEN; i++)
    {
        while (Swerve_getAngle(&rightModule) != pathArray[i][1])
        {
            Swerve_setAngleAbsolute(&leftModule, pathArray[i][1]);
            Swerve_setAngleAbsolute(&rightModule, pathArray[i][1]);
        }

        while (Swerve_getDist(&rightModule) != pathArray[i][0])
        {
            Swerve_driveDist(&leftModule, pathArray[i][0], 1);
            Swerve_driveDist(&rightModule, pathArray[i][0], 1);
        }
    }
}
