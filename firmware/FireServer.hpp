#pragma once
#include <Arduino.h>
#include <ESP8266WebServer.h>

class FireServer
{
public:
  void init();
  void update();

private:
  int serverPort = 80;
  ESP8266WebServer *server;
  void handleRoot();
  void handleNotFound();
};
