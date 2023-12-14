#include <Arduino.h>
#include <L293D.h>

#define MOTOR_A      1   // motor pin a
#define MOTOR_B      2   // motor pin b
#define MOTOR_ENABLE 3   // Enable (also PWM pin)

#define PWM_MOTOR_FREQUENCY   200
#define PWM_MOTOR_RESOLUTION    8

// Create motor object using given pins
L293D motor(MOTOR_A, MOTOR_B, MOTOR_ENABLE);

void setup() {  
    // begin --> true false, enables disables PWM, use given frequency and resolution
    motor.begin(true, PWM_MOTOR_FREQUENCY, PWM_MOTOR_RESOLUTION);
    // Speed -100%...0..100%
    motor.SetMotorSpeed(100);
}

void loop() {
}