#pragma once
#include <Arduino.h>
#include <FS.h>

class FileSystem
{
public:
  void init();
  bool wifiConfigured();

private:
  char *wifiConfigFile = "/config/wifi.json";
};