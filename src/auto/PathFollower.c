/*#include "PathTransformer.c"

void followPath(float pathArray[PATH_LEN][PATH_HEIGHT])
{
    for(int i = 0; i < PATH_LEN; i++)
    {
        stopTask(t_LPID_ControllerOne);
        stopTask(t_LPID_ControllerTwo);
    
	    Swerve_setDriveSpeed(left, 0);
	    Swerve_setDriveSpeed(right, 0);

        while (Swerve_getAngle(&rightModule) != pathArray[i][1])
        {
            
            Swerve_setAngleAbsolute(&leftModule, pathArray[i][1]);
            //Swerve_setAngleAbsolute(&rightModule, pathArray[i][1]);
        }

        while (Swerve_getDist(&rightModule) != pathArray[i][0])
        {
            //Swerve_setMotOneTarget(&rightModule, pathArray[i][2]);
            //Swerve_setMotTwoTarget(&rightModule, pathArray[i][2]);
            
            Swerve_setMotOneTarget(&leftModule, pathArray[i][2]);
            Swerve_setMotTwoTarget(&leftModule, pathArray[i][2]);
        }

        startTask(t_LPID_ControllerOne);
	    startTask(t_LPID_ControllerTwo);


    }
}
*/