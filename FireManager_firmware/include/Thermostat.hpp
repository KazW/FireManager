#pragma once
#include <Arduino.h>
#include <Thermocouple.h>
#include <MAX6675_Thermocouple.h>
#include "FileSystem.hpp"
#include "Parser.hpp"
#include "Blower.hpp"
#include "PID.hpp"
#include "Types.hpp"

class Thermostat
{
public:
  Thermostat(byte pinSCK, byte pinCS, byte pinSO);
  void init(FileSystem *filesystem, Parser *parser, Blower *blower);
  void update();
  float temperature;
  float setPoint;

private:
  bool shouldUpdate();
  void sample();
  Thermocouple *thermocouple;
  FileSystem *filesystem;
  Parser *parser;
  Blower *blower;
  PID *pid;
  byte pinSO;
  byte pinCS;
  byte pinSCK;
  pidGains gains;
  const int sampleRate = 1000;
  unsigned long lastSample;
};
