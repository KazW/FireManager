#include "../include/Thermometer.hpp"

Thermometer::Thermometer(byte pinSCK, byte pinCS, byte pinSO)
{
  this->pinSCK = pinSCK;
  this->pinCS = pinCS;
  this->pinSO = pinSO;
}

void Thermometer::init()
{
  this->thermocouple = new MAX6675_Thermocouple(pinSCK, pinCS, pinSO);
  sample();
  this->lastSample = millis();
  Serial.println("Initial temperature: " + String(temperature) + "F");
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
  this->temperature = thermocouple->readFahrenheit();
}

bool Thermometer::shouldSample()
{
  return millis() - lastSample >= sampleRate;
}

double Thermometer::getTemperature()
{
  return temperature;
}
