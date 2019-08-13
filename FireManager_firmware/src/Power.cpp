#include "../include/Power.hpp"

Power::Power(byte pin)
{
  this->pin = pin;
}

void Power::init()
{
  // pinMode(pin, WAKEUP_PULLUP);
}

void Power::update()
{
  if (restart)
    restartNow();
}

double Power::getBatteryVoltage()
{
  return batteryVoltage;
}

byte Power::getBatteryLevel()
{
  return 99;
}

bool Power::lowBattery()
{
  return batteryVoltage <= lowBatteryVoltage;
}

void Power::shouldRestart()
{
  this->restart = true;
}

void Power::restartNow()
{
  ESP.restart();
  delay(powerDelay);
}

void Power::setSleepStatus(bool sleepStatus)
{
  this->sleepStatus = sleepStatus;
}

void Power::setSleepTime(unsigned long sleepTime)
{
  this->sleepTime = sleepTime;
}
