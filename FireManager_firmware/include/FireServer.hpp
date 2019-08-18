#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>
#include "../include/Power.hpp"
#include "../include/FileSystem.hpp"
#include "../include/Network.hpp"
#include "../include/Parser.hpp"
#include "../include/Thermostat.hpp"
#include "../include/Blower.hpp"

class FireServer
{
public:
  void init(
      Power *,
      FileSystem *,
      Network *,
      Parser *,
      Thermostat *,
      Blower *);
  void update();

private:
  Power *power;
  FileSystem *filesystem;
  Network *network;
  Parser *parser;
  Thermostat *thermostat;
  Blower *blower;
  AsyncWebServer *server;
  int serverPort = 80;
  bool serverStarted;

  void handleGetStatus(AsyncWebServerRequest *);

  void handleGetWifiConfig(AsyncWebServerRequest *);
  void handleSetWifiConfig(AsyncWebServerRequest *, JsonVariant);

  void handleGetThermostatSetPoint(AsyncWebServerRequest *);
  void handleSetThermostatSetPoint(AsyncWebServerRequest *, JsonVariant);

  void handleNotFound(AsyncWebServerRequest *);
  DynamicJsonDocument getResponseBuffer();
};
