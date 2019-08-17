#pragma once
#include <Arduino.h>

class Power
{
public:
  Power(byte);
  void init();
  void update();
  float batteryVoltage = 4.20;
  byte getBatteryLevel();
  bool lowBattery();
  void setSleepStatus(bool);
  void setSleepTime(unsigned long);
  void shouldRestart();

private:
  bool restart;
  byte pin;
  bool sleepStatus = false;
  unsigned long sleepTime = 60 * 1e6;
  float lowBatteryVoltage = 3.7;
  int powerDelay = 100;
  void restartNow();
};
