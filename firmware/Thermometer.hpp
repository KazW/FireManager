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

private:
  byte pinSO;
  byte pinCS;
  byte pinCLK;
  MAX6675 *ktc;
  double temperature;
};
