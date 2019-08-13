#pragma once
#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>
#include "../include/Power.hpp"
#include "../include/FileSystem.hpp"
#include "../include/Network.hpp"
#include "../include/Parser.hpp"
#include "../include/Thermometer.hpp"

class FireServer
{
public:
  void init(Power *, FileSystem *, Network *, Parser *, Thermometer *);
  void update();

private:
  Power *power;
  FileSystem *filesystem;
  Network *network;
  Parser *parser;
  Thermometer *thermometer;
  AsyncWebServer *server;
  int serverPort = 80;
  bool serverStarted;

  void handleGetStatus(AsyncWebServerRequest *);
  void handleNotFound(AsyncWebServerRequest *);
  void handleSetWifiConfig(AsyncWebServerRequest *, JsonVariant);
  void handleGetWifiConfig(AsyncWebServerRequest *);
};
