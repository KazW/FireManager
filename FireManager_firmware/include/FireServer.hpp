#pragma once
#include <Arduino.h>
#include <WebServer.h>
#include "../include/FileSystem.hpp"
#include "../include/Network.hpp"
#include "../include/Parser.hpp"
#include "../include/Thermometer.hpp"

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
  WebServer *server;
  int serverPort = 80;
  bool serverStarted;

  void handleNotFound();
  bool handleFileRead(String);
  String getContentType(String *);
  void handleSetWifiConfig();
  void handleGetWifiConfig();
  void handleGetStatus();
};
