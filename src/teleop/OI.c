#include "JoystickDriver.c"
#include "../util/Constants.c"

short* getJoystickInput()
{

    getJoystickSettings(joystick);
    
    short strafePower = joystick.joy1_x1 / JOYSTICK_SCALAR;
    short forwardPower = joystick.joy1_y1 / JOYSTICK_SCALAR;

    short spinPower = joystick.joy1_x2 / JOYSTICK_SCALAR;

    short joystickInputs[3] = {0};

    joystickInputs[1] = strafePower;
    joystickInputs[2] = forwardPower;
    joystickInputs[3] = spinPower;

    return joystickInputs;

}