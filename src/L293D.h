#ifndef L293D_H
#define L293D_H

#define INVALID_PIN     -1

class L293D 
{

public:    
    #ifdef ESP32
        L293D(int MotorA, int MotorB, int enablePin = INVALID_PIN, int pwmChannel = 0);
    #else
        L293D(int MotorA, int MotorB, int enablePin = INVALID_PIN);
    #endif

    #ifdef ESP32
        bool begin(bool usePwm = true, int frequency = 1000, int resolution = 8);
    #else
        bool begin(bool usePwm = false);
    #endif

    bool FreeRun();
    bool Stop() { return SetMotorSpeed(0); }
    bool SetMotorSpeed(double speedPercent);
    double GetCurrentMotorSpeed() {return _currentSpeed;}

    // set pwm output in percentage to stop motor (default 100%, fast motor stop, could be set to 0, to disable pwm output for stopping the motor)
    void SetStopPWMValue(double pwm = 100) { _stopPWMValue = pwm; }
    
private:

    #ifdef ESP32
        bool SetupPwm(int frequency = 1000, int resolution = 8); 
        int _frequency;
        int _resolution;
        int _pwmChannel;
    #endif

    int _resolutionFactor;
    double _currentSpeed;
    bool _usePwm;
    int _enablePin;
    int _MotorA;
    int _MotorB;
    bool _initialized;

    double _stopPWMValue;
};


#endif