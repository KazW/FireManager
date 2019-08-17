#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>
#include "../include/Types.hpp"

class Parser
{
public:
  DynamicJsonDocument parseWifiConfig(String);
  DynamicJsonDocument getWifiConfigBuffer();
  wifiConfig castWifiConfig(DynamicJsonDocument);
  wifiConfig parseAndCastWifiConfig(String);
  int wifiConfigSize = JSON_OBJECT_SIZE(3) + 189;

  DynamicJsonDocument parseThermostatConfig(String);
  DynamicJsonDocument getThermostatConfigBuffer();
  thermostatConfig castThermostatConfig(DynamicJsonDocument);
  thermostatConfig parseAndCastThermostatConfig(String);
  int thermostatConfigSize = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + 104;
};
