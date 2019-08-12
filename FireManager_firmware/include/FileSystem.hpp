#pragma once
#include <Arduino.h>
#include <SPIFFS.h>

class FileSystem
{
public:
  void init();
  bool wifiClientConfigured();
  String getWifiConfig();
  bool setWifiConfig(String);
  char *getWebDir();

private:
  char *configDir = "/config";
  char *webDir = "/web";
  char *wifiConfigFile = "/config/wifi.json";
};
