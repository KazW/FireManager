#pragma once
#include <Arduino.h>
#include <ESP8266WebServer.h>
#include "FileSystem.hpp"
#include "Network.hpp"

class FireServer
{
public:
  void init(FileSystem *, Network *);
  void update();

private:
  FileSystem *filesystem;
  Network *network;
  int serverPort = 80;
  ESP8266WebServer *server;
  bool serverStarted;
  void handleRoot();
  void handleNotFound();
};
