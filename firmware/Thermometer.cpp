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
  delay(initDelay);
  sample();
  this->lastSample = millis();
}

void Thermometer::update()
{
  if (shouldSample())
  {
    sample();
    this->lastSample = millis();
  }
}

void Thermometer::sample()
{
  this->temperature = this->ktc->readFahrenheit();
  Serial.print("F = ");
  Serial.println(temperature);
}

bool Thermometer::shouldSample()
{
  return millis() - lastSample >= sampleRate;
}

double Thermometer::getTemperature()
{
  return temperature;
}
