#pragma once

typedef struct WiFiConfig wifiConfig;
struct WiFiConfig
{
  const char *ssid;
  const char *password;
  const char *host;
};

typedef struct PIDgains pidGains;
struct PIDgains
{
  float Kp;
  float Ki;
  float Kd;
};

typedef struct ThermostatConfig thermostatConfig;
struct ThermostatConfig
{
  float setPoint;
  pidGains gains;
};
