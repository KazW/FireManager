#pragma once
#include <Arduino.h>
#include <SPIFFS.h>

class FileSystem
{
public:
  void init();
  char *webDir = "/web";
  bool exists(char *);
  bool exists(const char *);

  const char *wifiConfigFile = "/config/wifi.json";
  bool wifiClientConfigured();
  String getWifiConfig();
  bool setWifiConfig(String);

  const char *thermostatConfigFile = "/config/thermostat.json";
  bool thermostatConfigured();
  String getThermostatConfig();
  bool setThermostatConfig(String);

private:
  String readFile(String);
  bool writeFile(String, String);
  char *configDir = "/config";
};
