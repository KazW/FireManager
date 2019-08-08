#include "Power.hpp"

Power::Power(byte pin)
{
  this->pin = pin;
}

void Power::init()
{
  pinMode(pin, WAKEUP_PULLUP);
}

double Power::batteryVoltage()
{
  return 4.20;
}

void Power::sleepNow(unsigned long duration)
{
  ESP.deepSleep(duration);
}

void Power::setSleepStatus(bool sleepStatus)
{
  this->sleepStatus = sleepStatus;
}

void Power::setSleepTime(unsigned long sleepTime)
{
  this->sleepTime = sleepTime;
}

void Power::update()
{
  if (sleepStatus)
    sleepNow(sleepTime);
}
