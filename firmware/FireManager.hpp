#pragma once

#include <Arduino.h>
#include "Power.hpp"
#include "Thermometer.hpp"
#include "Network.hpp"

class FireManager
{
public:
  FireManager(Power *, Thermometer *, Network *);
  void init();
  void update();

private:
  // Hardware and Peripherals
  Power *power;
  Thermometer *thermometer;
  Network *network;

  // State
  bool alarm;

  // Constants
  double temperaturePowerThreshold = 125;
  int lowBatterySleepTime = 5 * 60 * 1e6;
  int updateDelay = 1000;

  // Functions
  void verify();
  void detect();
};
