#pragma once
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include "FileSystem.hpp"
#include "Parser.hpp"
#include "Types.hpp"

class Network
{
public:
  void init(FileSystem *, Parser *);
  void update();
  bool online();
  bool wifiClient();

private:
  void startWiFiAp();
  void startWiFiClient();
  void startmDNS();

  FileSystem *filesystem;
  Parser *parser;
  WiFiConfig config;

  const char *apSSID = "FireManager";
  const char *apPassword = "start-my-fire";
  const char *apHost = "fire-manager";
  IPAddress apIP = IPAddress(192, 168, 0, 1);
  IPAddress apGateway = IPAddress(192, 168, 0, 1);
  IPAddress apSubnet = IPAddress(255, 255, 255, 0);

  bool clientMode;
  const char *hostname;
  bool wifiOnline;
  bool mDNSOnline;
};
