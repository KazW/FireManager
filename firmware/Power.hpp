#pragma once
#include <Arduino.h>

class Power
{
public:
  Power(byte);
  void init();
  void update();
  double getBatteryVoltage();
  bool lowBattery();
  void setSleepStatus(bool);
  void setSleepTime(unsigned long);
  void sleepNow(unsigned long);

private:
  byte pin;
  bool sleepStatus = false;
  unsigned long sleepTime = 60 * 1e6;
  double batteryVoltage = 4.20;
  double lowBatteryVoltage = 3.7;
  int deepSleepDelay = 500;
};
