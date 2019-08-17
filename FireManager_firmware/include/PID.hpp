#pragma once
#include <Arduino.h>
#include <math.h>
#include "Types.hpp"

class PID
{
public:
  PID(
      pidGains *,
      float *processValue,
      float *setPoint,
      const int *dt,
      const byte *min,
      const byte *max,
      byte *output);
  void calculate();

private:
  float *processValue;
  pidGains *gains;
  float *setPoint;
  const int *dt;
  const byte *min;
  const byte *max;
  byte *output;
  float previousError = 0;
  float integral = 0;
};
