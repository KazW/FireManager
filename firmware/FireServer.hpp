#pragma once
#include <Arduino.h>
#include <ESP8266WebServer.h>
#include "FileSystem.hpp"
#include "Network.hpp"
#include "Parser.hpp"
#include "Thermometer.hpp"

class FireServer
{
public:
  void init(FileSystem *, Network *, Parser *, Thermometer *);
  void update();

private:
  FileSystem *filesystem;
  Network *network;
  Parser *parser;
  Thermometer *thermometer;
  ESP8266WebServer *server;
  int serverPort = 80;
  bool serverStarted;

  void handleNotFound();
  bool handleFileRead(String);
  String getContentType(String *);
  void handleSetWifiConfig();
  void handleGetWifiConfig();
  void handleGetStatus();
};
