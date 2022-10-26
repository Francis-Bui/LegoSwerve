#ifndef PID_H
#define PID_H

//macro declaration
#define MAX_VAL 100
#define GUARD 22
#define LEVEL 20

//class declaration
class PID{
    
    public:
	PID(double, double);
    PID(double, double, double, double, double);
	double update(double);
    double update(double, double);
    void parameter(double, double);
    void clear();
    void setSampleTime(double);
	void setRefMinMax(double, double);
    
    private:
    double Kp;
    double Ki;
    double Kd;
    double current_time;
    double SampleTime;
    double last_time;
    double SetPoint;
    double PTerm;
    double ITerm;
    double DTerm;
    double windup_guard;
    double output;
    double error;
    double delta_time;
    double delta_error;
    double last_error;
    double minREF;
    double maxREF;
    size_t cnt;
};

#include "PID.cpp"

#endif