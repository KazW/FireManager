#include "../include/Parser.hpp"

DynamicJsonDocument Parser::getWifiConfigBuffer()
{
  DynamicJsonDocument data(wifiConfigSize);
  return data;
}

DynamicJsonDocument Parser::parseWifiConfig(String rawConfig)
{
  DynamicJsonDocument data = getWifiConfigBuffer();
  deserializeJson(data, rawConfig);

  return data;
}

wifiConfig Parser::castWifiConfig(DynamicJsonDocument data)
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

DynamicJsonDocument Parser::getThermostatConfigBuffer()
{
  DynamicJsonDocument data(thermostatConfigSize);
  return data;
}

DynamicJsonDocument Parser::parseThermostatConfig(String rawConfig)
{
  DynamicJsonDocument data = getThermostatConfigBuffer();
  deserializeJson(data, rawConfig);

  return data;
}

thermostatConfig Parser::castThermostatConfig(DynamicJsonDocument data)
{
  thermostatConfig config;
  pidGains gains;

  config.setPoint = data["setPoint"] | 250.0;

  JsonObject gainsData = data["gains"];
  gains.Kp = gainsData["Kp"] | 20.0;
  gains.Ki = gainsData["Ki"] | 100.0;
  gains.Kd = gainsData["Kd"] | 30.0;

  config.gains = gains;
  return config;
}

thermostatConfig Parser::parseAndCastThermostatConfig(String config)
{
  return castThermostatConfig(parseThermostatConfig(config));
}
