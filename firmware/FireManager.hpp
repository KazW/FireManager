#pragma once
#include <Arduino.h>
#include "Power.hpp"
#include "FileSystem.hpp"
#include "Parser.hpp"
#include "Thermometer.hpp"
#include "Network.hpp"
#include "FireServer.hpp"

class FireManager
{
public:
  FireManager(
      Power *,
      FileSystem *,
      Parser *,
      Thermometer *,
      Network *,
      FireServer *);
  void init();
  void update();

private:
  // Functions
  void verify();
  void detect();

  // Hardware and Peripherals
  Power *power;
  FileSystem *filesystem;
  Parser *parser;
  Thermometer *thermometer;
  Network *network;
  FireServer *server;

  // State
  bool alarm;

  // Constants
  double temperaturePowerThreshold = 125;
  unsigned long lowBatterySleepTime = 5 * 60 * 1e6;
};
