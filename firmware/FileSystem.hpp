#pragma once
#include <Arduino.h>
#include <FS.h>

class FileSystem
{
public:
  void init();
  bool wifiConfigured();
  char *getWifiConfig();

private:
  char *configDir = "/config";
  char *wifiConfigFile = "/config/wifi.json";
};
