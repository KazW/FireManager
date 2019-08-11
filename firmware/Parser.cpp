#include "Parser.hpp"

ArduinoJson6113_00000::DynamicJsonDocument Parser::getWifiConfigBuffer()
{
  DynamicJsonDocument data(wifiConfigSize);
  return data;
}

ArduinoJson6113_00000::DynamicJsonDocument Parser::parseWifiConfig(String rawConfig)
{
  ArduinoJson6113_00000::DynamicJsonDocument data = getWifiConfigBuffer();
  Serial.print("Parsing wifi config: ");
  Serial.println(rawConfig);
  deserializeJson(data, rawConfig);

  return data;
}

wifiConfig Parser::castWifiConfig(ArduinoJson6113_00000::DynamicJsonDocument data)
{
  wifiConfig config;

  config.ssid = data["ssid"];
  config.password = data["password"];
  config.host = data["host"];

  return config;
}

wifiConfig Parser::parseAndCastWifiConfig(String config)
{
  return castWifiConfig(parseWifiConfig(config));
}

int Parser::getwifiConfigSize()
{
  return wifiConfigSize;
}
