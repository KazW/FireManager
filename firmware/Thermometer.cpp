#include "Thermometer.hpp"

Thermometer::Thermometer(byte pinCLK, byte pinCS, byte pinSO)
{
  this->pinCLK = pinCLK;
  this->pinCS = pinCS;
  this->pinSO = pinSO;
}

void Thermometer::init()
{
  MAX6675 ktc = MAX6675(pinCLK, pinCS, pinSO);
  this->ktc = &ktc;
  delay(500);
  update();
}

void Thermometer::update()
{
  double temperature = this->ktc->readFahrenheit();
  this->temperature = temperature;
  Serial.print("F = ");
  Serial.println(temperature);
}

double Thermometer::getTemperature()
{
  return temperature;
}
