#include <Arduino.h>
#include <L293D.h>

//Pin 1, 2, 3 and PWM channel 0
L293D motor(1, 2, 3, 0);

void setup() {  
    motor.begin();     
    motor.SetMotorSpeed(100);
}

void loop() {
}