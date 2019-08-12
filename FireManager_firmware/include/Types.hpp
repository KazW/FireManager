#pragma once

typedef struct WiFiConfig wifiConfig;
struct WiFiConfig
{
  const char *ssid;
  const char *password;
  const char *host;
};
