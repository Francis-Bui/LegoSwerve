#include "JoystickDriver.c"

const float JOYSTICK_SCALAR = 1.27;

float* getJoystickInput()
{

    getJoystickSettings(joystick);

    float strafePower = joystick.joy1_x1 / JOYSTICK_SCALAR;
    float forwardPower = joystick.joy1_y1 / JOYSTICK_SCALAR;

    float spinPower = joystick.joy1_x2 / JOYSTICK_SCALAR;

    float joystickInputs[3] = {0,0,0};

    joystickInputs[0] = strafePower;
    joystickInputs[1] = forwardPower;
    joystickInputs[2] = spinPower;

    return &joystickInputs;

}
