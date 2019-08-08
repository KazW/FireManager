#pragma once
#include "Secrets.hpp"
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

class Network
{
public:
  void init();
  void update();
  bool online();

private:
  void startWiFi();
  void startmDNS();
  bool wifiOnline;
  bool mDNSOnline;
  int connectDelay = 250;
  int maxConnectDelays = 4 * 30;
};
