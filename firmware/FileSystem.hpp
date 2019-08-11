#pragma once
#include <Arduino.h>
#include <FS.h>

class FileSystem
{
public:
  void init();
  bool wifiConfigured();
  String getWifiConfig();
  bool setWifiConfig(String);
  char *getWebDir();

private:
  char *configDir = "/config";
  char *webDir = "/web";
  char *wifiConfigFile = "/config/wifi.json";
};
