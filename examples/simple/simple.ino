#include <Arduino.h>
#include <L293D.h>

//Pin 1, 2, 3 and PWM channel 0
//          A  B En, channel
L293D motor(1, 2, 3);

void setup() {  
    motor.begin();
    // Speed -100%...0..100%
    motor.SetMotorSpeed(100);
}

void loop() {
}