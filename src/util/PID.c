
typedef struct PIDController{
	float pidIntegral;
	float pidDerivative;
	float pidDrive;
	float pidLastError;

	float maxOutput;
	float minOutput;

	float kP;
	float kI;
	float kD;

	float integralLimit;
	float target; // variable is used by drive straight controller
} PIDController;
 

/**
 * Initializes PID constants for controller. 
*/
void PID_initPIDConstants(PIDController *controller, float p, float i, float d, float integralLimit)
{
	controller -> kP = p;
	controller -> kI = i;
	controller -> kD = d;
	controller -> integralLimit = integralLimit;
}

/**
 * Initializes PID output range for controller.
*/
void PID_initOutputRange(PIDController *controller, float max, float min)
{
	controller -> maxOutput = max;
	controller -> minOutput = min;
}


/**
 * Resets pid integral and derivative values. Called
 * before starting a pid task. 
 * Written by Akil Pathiranage
*/
void PID_reset(PIDController *controller)
{
	controller -> pidLastError = 0;
	controller -> pidIntegral = 0;
	controller -> pidDerivative = 0;
}

/**
 * Main drive function for PID controllers, takes in an error and a controller to 
 * calculate drive with. 
 * Written by Akil Pathiranage
*/
float PID_calculateDrive(PIDController *controller, float error)
{
	float drive;

	//integral calculation
	if(controller -> kI != 0 && controller -> pidIntegral < controller -> integralLimit)
		controller -> pidIntegral += error;
	if(controller -> pidIntegral > controller -> integralLimit)
		controller -> pidIntegral = controller -> integralLimit;
		
			
	//derivative calculation calculation
	float derivative = error - (controller -> pidLastError);
	controller -> pidLastError = error;

	drive = (controller -> kP)*error + (controller -> kI)*(controller -> pidIntegral) + (controller -> kD)*derivative;

	//clamping drive value
	if(drive > controller -> maxOutput)
	drive = controller -> maxOutput;

	if (drive < controller -> minOutput)
	drive = controller -> minOutput;

	return drive;
}
