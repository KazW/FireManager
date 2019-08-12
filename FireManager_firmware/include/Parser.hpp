#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>
#include "../include/Types.hpp"

class Parser
{
public:
  ArduinoJson6113_00000::DynamicJsonDocument parseWifiConfig(String);
  ArduinoJson6113_00000::DynamicJsonDocument getWifiConfigBuffer();
  wifiConfig castWifiConfig(ArduinoJson6113_00000::DynamicJsonDocument);
  wifiConfig parseAndCastWifiConfig(String);
  int getwifiConfigSize();

private:
  int wifiConfigSize = JSON_OBJECT_SIZE(3) + 189;
};
