#ifndef L293D_H
#define L293D_H

#define INVALID_PIN     -1

class L293D {

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
    bool SetMotorSpeed(int speed);
    
private:

    #ifdef ESP32
    bool SetupPwm(int frequency = 1000, int resolution = 8); // , int resolution);
    int _frequency;
    int _resolution;
    int _pwmChannel;
    #endif

    int _currentSpeed;
    bool _usePwm;
    int _enablePin;
    int _MotorA;
    int _MotorB;
    bool _initialized;
};



#endif