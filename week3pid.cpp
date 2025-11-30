#include <cstdio>
#include <cstdint>


int t = 10; //fake time reading (real time doesn't work on this sim)

long us_ticker_read_test(){
    return t;
}

class PIDClass{
public:
    
    PIDClass(double kP, double kI, double kD);
    double calculate(double error);
    
private:
    
    double kP, kI, kD; //constants 

    long lastTime; //timestamp of the previous time
    double lastError; //error of previous frame
    double errorIntegral; //integral of error
    
    double calculateP(double error); 
    double calculateI(double error);
    double calculateD(double error);
};
///////////////
//PID.cpp
///////////////

//include PID.h //not neccessary here as we are using one file for everything.

PIDClass::PIDClass(double kP, double kI, double kD)
: kP(kP), kI(kI), kD(kD),
  lastTime(0),
  lastError(0.0),
  errorIntegral(0.0)
{
}

/*
 * Calculates the P section for our PID algorithm.
 * @param error The current error
 * @return the output from this calculation
 */
double PIDClass::calculateP(double error){
    return kP * error;
}

/*
 * Calculates the I section for our PID algorithm.
 * @param error The current error
 * @return the output from this calculation
 */
double PIDClass::calculateI(double error){
    long currentTime = us_ticker_read_test();
    double dt = (lastTime == 0) ? 0.0 : (currentTime - lastTime) / 1000.0;
    errorIntegral += error * dt;
    return kI * errorIntegral;
}

/*
 * Calculates the D section for our PID algorithm.
 * @param error The current error
 * @return the output from this calculation
 */
double PIDClass::calculateD(double error){
    long currentTime = us_ticker_read_test();
    double dt = (lastTime == 0) ? 0.0 : (currentTime - lastTime) / 1000.0;
    double dEdt = (dt > 0.0) ? (error - lastError) / dt : 0.0;
    return kD * dEdt;
}

/*
 * Calculates the output for our PID algorithm.
 * @param error The current error
 * @return the output from this calculation
 */
double PIDClass::calculate(double error){
    double result = calculateP(error) + calculateI(error) + calculateD(error);
    
    lastTime = us_ticker_read_test();
    lastError = error;

    return result;
}

///////////////
//main.cpp // DO NOT EDIT PERMANENTLY BELOW
///////////////

//#include "PID.cpp" //not neccessary here again as we are using one file for everything.

bool debugCode = true;

int main(){
    PIDClass testP(3.2,0,0);
    PIDClass testI(0,0.21,0);
    PIDClass testD(0,0,42.0);
    
    PIDClass testAll(3.2,0.21,42.0);
    
    double errors[25] = {1.34,1.144,0.838,0.425,-0.037,-0.454,-0.751,-0.917,-0.985,-1,-0.993,-0.961,-0.919,-0.838,-0.713,-0.562,-0.408,-0.269,-0.15,-0.052,0.029,0.095,0.151,0.198};
    
    for(int i = 0; i < 25; i ++){
        if(debugCode){
            printf("Results at time %d: P: %f, I: %f D: %f All: %f\n", t,
                testP.calculate(errors[i]),
                testI.calculate(errors[i]),
                testD.calculate(errors[i]),
                testAll.calculate(errors[i])
                );
        }
        t+=10;
    }
}
