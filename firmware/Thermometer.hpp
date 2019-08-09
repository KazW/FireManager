#pragma once
#include <Arduino.h>
#include <max6675.h>

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
  byte pinCLK;
  MAX6675 *ktc;
  int initDelay = 1000;
  unsigned long sampleRate = 1e6;
  unsigned long lastSample;
  double temperature;
};
