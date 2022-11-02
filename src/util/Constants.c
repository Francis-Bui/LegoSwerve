const float radius = 10.0;
const float trackWidth = 10.0; //radius * cos(pi/4);
const float wheelBase = 10.0; //radius * sin(pi/4)

const float ANGLE_TOL = 2.0;
const float DIST_TOL = 5.0;
const float maxSpeed = 0.0;

char leftGyroPort[3] = "S1";
char rightGyroPort[2] = "S2";

// These motors are declared here to stop vscode from glowing with errors -- remove before deployment.
int motor[1] = {2}; 
int motorA = 1;
int motorB = 2;
int motorC = 3;
int motorD = 4;
int buttonRight = 0;
int buttonLeft = 0;
int true = 1;

typedef unsigned char task;


