#include "../include/Thermostat.hpp"

Thermostat::Thermostat(byte pinSCK, byte pinCS, byte pinSO)
{
  this->pinSCK = pinSCK;
  this->pinCS = pinCS;
  this->pinSO = pinSO;
}

void Thermostat::init(FileSystem *filesystem, Parser *parser, Blower *blower)
{
  this->thermocouple = new MAX6675_Thermocouple(pinSCK, pinCS, pinSO);
  this->blower = blower;
  this->filesystem = filesystem;
  this->parser = parser;
  thermostatConfig config = parser->parseAndCastThermostatConfig(
      this->filesystem->getThermostatConfig());

  this->setPoint = config.setPoint;
  this->gains = config.gains;

  sample();
  this->lastSample = millis();
  Serial.println("Initial temperature: " + String(temperature) + "F");

  this->pid = new PID(
      &temperature,
      &this->blower->level,
      &setPoint,
      gains.Kp,
      gains.Ki,
      gains.Kd,
      P_ON_M,
      DIRECT);
  this->pid->SetMode(AUTOMATIC);
}

void Thermostat::update()
{
  if (shouldSample())
  {
    sample();
    this->lastSample = millis();
  }
  pid->Compute();
}

void Thermostat::sample()
{
  this->temperature = thermocouple->readFahrenheit();
}

bool Thermostat::shouldSample()
{
  return millis() - lastSample >= sampleRate;
}
