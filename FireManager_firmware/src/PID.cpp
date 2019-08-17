#include "../include/PID.hpp"

PID::PID(
    PIDgains *gains,
    float *processValue,
    float *setPoint,
    const int *dt,
    const byte *min,
    const byte *max,
    byte *output)
{
  this->gains = gains;
  this->processValue = processValue;
  this->setPoint = setPoint;
  this->dt = dt;
  this->min = min;
  this->max = max;
  this->output = output;
}

void PID::calculate()
{
  // Calculate error
  float error = *setPoint - *processValue;

  // Proportional term
  float Pout = this->gains->Kp * error;

  // Integral term
  integral += error * *dt;
  float Iout = this->gains->Ki * integral;

  // Derivative term
  float derivative = (error - previousError) / *dt;
  float Dout = this->gains->Kd * derivative;

  // Calculate total value
  float value = Pout + Iout + Dout;

  // Restrict to max/min
  if (value > float(*max))
    value = float(*max);
  else if (value < float(*min))
    value = float(*min);

  // Save error to previous error
  previousError = error;

  // Write output value
  *output = byte(value);
}
