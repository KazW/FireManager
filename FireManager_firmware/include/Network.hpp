#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>
#include "../include/Power.hpp"
#include "../include/FileSystem.hpp"
#include "../include/Parser.hpp"
#include "../include/Types.hpp"

class Network
{
public:
  void init(Power *, FileSystem *, Parser *);
  void update();
  bool wifiClient();

private:
  void startWiFiAp();
  void startWiFiClient();
  void startmDNS();

  Power *power;
  FileSystem *filesystem;
  Parser *parser;
  WiFiConfig config;

  const char *apSSID = "FireManager";
  const char *apPassword = "start-my-fire";
  const char *apHost = "fire-manager";
  IPAddress apIP = IPAddress(192, 168, 0, 1);
  IPAddress apGateway = IPAddress(192, 168, 0, 1);
  IPAddress apSubnet = IPAddress(255, 255, 255, 0);

  bool clientConfigured;
  const char *hostname;
  bool wifiClientOnline;
  bool wifiApOnline;
  bool mDNSOnline;
};
