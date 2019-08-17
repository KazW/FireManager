#pragma once
#include <Arduino.h>
#include <Thermocouple.h>
#include <MAX6675_Thermocouple.h>
#include <PID_v1.h>
#include "FileSystem.hpp"
#include "Parser.hpp"
#include "Blower.hpp"
#include "Types.hpp"

class Thermostat
{
public:
  Thermostat(byte pinSCK, byte pinCS, byte pinSO);
  void init(FileSystem *filesystem, Parser *parser, Blower *blower);
  void update();
  double temperature;
  double setPoint;

private:
  void sample();
  bool shouldSample();
  Thermocouple *thermocouple;
  FileSystem *filesystem;
  Parser *parser;
  Blower *blower;
  PID *pid;
  byte pinSO;
  byte pinCS;
  byte pinSCK;
  pidGains gains;
  const int sampleRate = 200;
  unsigned long lastSample;
};
