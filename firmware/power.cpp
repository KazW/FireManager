#include "Power.hpp"

Power::Power(byte pin)
{
  this->pin = pin;
}

void Power::init()
{
  pinMode(pin, WAKEUP_PULLUP);
}

void Power::update()
{
  if (sleepStatus)
    sleepNow(sleepTime);
}

double Power::getBatteryVoltage()
{
  return batteryVoltage;
}

bool Power::lowBattery()
{
  return batteryVoltage <= lowBatteryVoltage;
}

void Power::sleepNow(unsigned long duration)
{
  ESP.deepSleep(duration);
  delay(deepSleepDelay);
}

void Power::setSleepStatus(bool sleepStatus)
{
  this->sleepStatus = sleepStatus;
}

void Power::setSleepTime(unsigned long sleepTime)
{
  this->sleepTime = sleepTime;
}
