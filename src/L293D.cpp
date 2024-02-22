#include <Arduino.h>
#include "L293D.h"

#ifdef ESP32
  L293D::L293D(int MotorA, int MotorB, int enablePin, int pwmChannel)
#else
  L293D::L293D(int MotorA, int MotorB, int enablePin)
#endif
{
  _MotorA = MotorA;
  _MotorB = MotorB;
  _enablePin = enablePin;
  _initialized = false;
  _currentSpeed = 0;
  _usePwm = false;
  _resolutionFactor = 255;
  _stopPWMValue = 100;

#ifdef ESP32
  _frequency = 1000;
  _resolution = 8;
  _pwmChannel = pwmChannel;
  _resolutionFactor = (1<<_resolution) - 1;
#endif

}

#ifdef ESP32
  bool L293D::begin(bool usePwm, int frequency, int resolution)
#else
  bool L293D::begin(bool usePwm)
#endif
{
  if ((_MotorA == INVALID_PIN && _MotorB == INVALID_PIN) || (usePwm && _enablePin == INVALID_PIN))
    return false;

  _usePwm = usePwm;
  if (usePwm)
  {
#ifdef ESP32
    SetupPwm(frequency, resolution);
#endif
  }
  else
    pinMode(_enablePin, OUTPUT);

  if (_MotorA != INVALID_PIN)
    pinMode(_MotorA, OUTPUT);
  if (_MotorB != INVALID_PIN)
    pinMode(_MotorB, OUTPUT);

  _initialized = true;
  return true;
}

#ifdef ESP32
bool L293D::SetupPwm(int frequency, int resolution)
{
  if (_enablePin == INVALID_PIN || !_usePwm)
    return false;

  _frequency = frequency;
  _resolution = resolution;
  _resolutionFactor = (1<<_resolution) - 1;  

  if (_initialized)
    ledcDetachPin(_enablePin);
  ledcSetup(_pwmChannel, _frequency, _resolution);
  ledcAttachPin(_enablePin, _pwmChannel);

  return true;
}
#endif

bool L293D::FreeRun()
{
  if (!_initialized)
    return false;

  if (_usePwm)
  {
#ifdef ESP32
  ledcWrite(_pwmChannel, 0);
#else
  analogWrite(_enablePin, 0);
#endif
  }
  else
    digitalWrite(_enablePin, LOW);


  if (_MotorA != INVALID_PIN)
    digitalWrite(_MotorA, HIGH);
  if (_MotorB != INVALID_PIN)
    digitalWrite(_MotorB, HIGH);
  
  return true;
}

bool L293D::SetMotorSpeed(double speedPercent)
{
  if (!_initialized)
    return false;

  if (_MotorA != INVALID_PIN)
    digitalWrite(_MotorA, speedPercent > 0 ? HIGH : LOW);
  if (_MotorB != INVALID_PIN)
    digitalWrite(_MotorB, speedPercent < 0 ? HIGH : LOW);

  if (_usePwm)
  {
    double internalSpeed;
    
    // in case 0, stop motor, use LOW for both Motor_A and Motor_B and High for Enable --> Fast motor stop (can be changed by SetStopPWMValue)
    //EN  1A  2A  FUNCTION(1)
    //H    L   L  Fast motor stop
    //H    H   H  Fast motor stop
    //L    X   X  Free-running motor stop    
    if (speedPercent == 0)
    {
      // deafult max PWM --> HIGH for fast motor stop, or use changed _stopPWMValue
      internalSpeed = _stopPWMValue * _resolutionFactor / 100.0; 
    }
    else
    {
      // scale 0..100% to 0..resolution PWM i.e 8 Bit ==>  max 255 PWM
      internalSpeed = speedPercent * _resolutionFactor / 100.0;
    }


#ifdef ESP32
    ledcWrite(_pwmChannel, internalSpeed >= 0 ? internalSpeed : -internalSpeed);
#else
    analogWrite(_enablePin, internalSpeed >= 0 ? internalSpeed : -internalSpeed);
#endif
  }
  else
  {
    digitalWrite(_enablePin, HIGH);
  }

  _currentSpeed = speedPercent;

  return true;
}
