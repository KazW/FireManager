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
  double lowBatteryVoltage = 3.7;
  double temperaturePowerThreshold = 125;

  // Functions
  void verify();
  void detect();
};
