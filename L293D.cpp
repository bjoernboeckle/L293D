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
  _frequency = 1000;
  _resolution = 8;

  _currentSpeed = 0;
  _usePwm = false;
  _pwmChannel = pwmChannel;
}

#ifdef ESP32
bool L293D::begin(bool usePwm, int frequency, int resolution)
#else
bool L293D::begin(bool usePwm)
#endif
{
  if (_MotorA == INVALID_PIN || (usePwm && _enablePin == INVALID_PIN))
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

  if (_initialized)
    ledcDetachPin(_enablePin);
  ledcSetup(_pwmChannel, _frequency, _resolution);
  ledcAttachPin(_enablePin, _pwmChannel);

  return true;
}
#endif

bool L293D::SetMotorSpeed(int speed)
{
  if (!_initialized)
    return false;

  digitalWrite(_MotorA, speed > 0 ? HIGH : LOW);
  if (_MotorB != INVALID_PIN)
    digitalWrite(_MotorB, speed < 0 ? HIGH : LOW);

  if (_usePwm)
  {
    // scale 0..100% to 0..255 PWM
    int internalSpeed = speed * 255 / 100;
#ifdef ESP32
    ledcWrite(_pwmChannel, internalSpeed >= 0 ? internalSpeed : -internalSpeed);
#else
    analogWrite(internalSpeed);
#endif
  }
  else
  {
    digitalWrite(_pwmChannel, speed == 0 ? LOW : HIGH);
  }

  _currentSpeed = speed;

  return true;
}
