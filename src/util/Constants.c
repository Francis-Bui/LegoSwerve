const float GEAR_RADIUS = 52.3875; // Differential Gear OD is 4.125in, radius is 52.3875mm
const float WHEEL_RADIUS = 33.3375;
const float DIFF_TO_WHEEL = 3.50;
const float NET_GEAR_RATIO = 1.75;
const float TRACK_WIDTH = 10.0; //radius * cos(pi/4);
const float WHEEL_BASE = 10.0; //radius * sin(pi/4)
const float ENCODER_TO_ANGLE = 0.5;
const float ANGULAR_SPEED = 100.0;

const float POWER_RATE = 96.49; // rate of motor power to top speed.

const float ANGLE_TOL = 2.0;
const float DIST_TOL = 5.0;
const float MAX_SPEED = 0.0;

// AUTO CONSTANTS

const int PATH_LEN = 13;
const int PATH_HEIGHT = 3;

//PID arrays formatted as
// arr = {p, i ,d ,integral limit, max, min}
const float L_SPEED_ONE[6]=
{
    .585,
    0.0375,
    0.0035,
    0.00025,
    100,
    -100,
};
const float L_SPEED_TWO[6]=
{
    .585,
    0.0375,
    0.0035,
    0.00025,
    100,
    -100,
};
const float R_SPEED_ONE[6]=
{
    .585,
    0.0375,
    0.0035,
    0.00025,
    100,
    -100,
};
const float R_SPEED_TWO[6]=
{
    .585,
    0.0375,
    0.0035,
    0.00025,
    100,
    -100,
};

const float L_ANGLE_ONE[6]=
{
    2.23,
    0.0375,
    0.0035,
    0.00025,
    100,
    -100,
};
const float L_ANGLE_TWO[6]=
{
    2.23,
    0.0375,
    0.0035,
    0.00025,
    100,
    -100,
};
const float R_ANGLE_ONE[6]=
{
    4,
    0.020,
    0,
    0.00025,
    100,
    -100,
};
const float R_ANGLE_TWO[6]=
{
    4,
    0.025,
    0,
    0.00025,
    100,
    -100,
};



// These motors are declared here to stop vscode from glowing with errors -- remove before deployment.

/*
int motor[1] = {2};
int motorA = 1;
int motorB = 2;
int motorC = 3;
int motorD = 4;
int buttonRight = 0;
int buttonLeft = 0;
typedef unsigned char task;

typedef int bool;
*/

#define true 1
#define false 0
