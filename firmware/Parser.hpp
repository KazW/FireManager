#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>
#include "FileSystem.hpp"
#include "Types.hpp"

class Parser
{
public:
  void init(FileSystem *);
  wifiConfig parseWifiConfig();

private:
  FileSystem *filesystem;
  int configJSONSize = JSON_OBJECT_SIZE(3) + 229;
};
