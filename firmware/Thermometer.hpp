#pragma once
#include <Arduino.h>
#include <Thermocouple.h>
#include <MAX6675_Thermocouple.h>

class Thermometer
{
public:
  Thermometer(byte, byte, byte);
  void init();
  void update();
  double getTemperature();
  bool shouldSample();

private:
  void sample();
  byte pinSO;
  byte pinCS;
  byte pinSCK;
  Thermocouple *thermocouple;
  int initDelay = 1000;
  unsigned long sampleRate = 1000;
  unsigned long lastSample;
  double temperature;
};
