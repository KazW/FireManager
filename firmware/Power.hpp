#pragma once
#include <Arduino.h>

class Power
{
public:
  Power(byte);
  void init();
  void update();
  double batteryVoltage();
  void setSleepStatus(bool);
  void setSleepTime(unsigned long);
  void sleepNow(unsigned long);

private:
  byte pin;
  bool sleepStatus = false;
  unsigned long sleepTime = 60 * 1e6;
};
