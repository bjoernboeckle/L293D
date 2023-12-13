# L293D

This repository contains a library to control a motror connected to an H-Bridge (i.e. L293D), that can be used with Arduino and ESP32. 

The ESP32 version can also configure the PWM frequency and resolution.
Also the ESP32 version requires a channel for the PWM pin.

# Quick start

## Simple example ESP32


```c++
#include <Arduino.h>
#include <L293D.h>

//Pin 1, 2, 3 and PWM channel 0
//          A  B En, channel
L293D motor(1, 2, 3, 0);

void setup() {  
    motor.begin();     
    // Speed -100%...0..100%
    motor.SetMotorSpeed(100);
}

void loop() {
}
```


## Simple example Arduino


```c++
#include <Arduino.h>
#include <L293D.h>

//Pin 1, 2, 3
//          A  B  En
L293D motor(1, 2, 3);

void setup() {  
    motor.begin();
    // Speed -100%...0..100%
    motor.SetMotorSpeed(100);
}

void loop() {
}
```

# Usage

Create a motor, either only one direction or two directions including enable(pwm).
Using Pin1 and Pin2 to connect to the motor, and pin3 for pwm and using pwm channel 0 (not supported for Arduino).
In case Pin is -1 (not set)

```c++
L293D motor(1, 2, 3, 0);
```

Initialize pins etc.
Optional parameter to set PWM mode and also PWM frequency.

```c++
motor.begin(true, 1000); 
```



## Methods

```c++
//ESP32
    L293D(int Motor1, int Motor2 = -1, int enablePin = -1, int pwmChannel = 0);
    bool begin(bool usePwm = false, int frequency = 1000, int resolution = 8);

// Arduino
    L293D::L293D(int MotorA, int MotorB, int enablePin);
    bool begin(bool usePwm = false);

bool Stop();
bool SetMotorSpeed(int speed);
```