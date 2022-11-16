const float RADIUS = 10.0;
const float TRACK_WIDTH = 10.0; //radius * cos(pi/4);
const float WHEEL_BASE = 10.0; //radius * sin(pi/4)

const float ANGLE_TOL = 2.0;
const float DIST_TOL = 5.0;
const float MAX_SPEED = 0.0;

const float L_CTRL_ONE[6]=
{
    0,
    0,
    0,
    0,
    1,
    -1,
};
const float L_CTRL_TWO[6]=
{
    0,
    0,
    0,
    0,
    1,
    -1,
};
const float R_CTRL_ONE[6]=
{
    0,
    0,
    0,
    0,
    1,
    -1,
};
const float R_CTRL_TWO[6]=
{
    0,
    0,
    0,
    0,
    1,
    -1,
};



// These motors are declared here to stop vscode from glowing with errors -- remove before deployment.
#define true 1
#define false 0
