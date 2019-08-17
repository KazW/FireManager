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
  double Kp;
  double Ki;
  double Kd;
};

typedef struct ThermostatConfig thermostatConfig;
struct ThermostatConfig
{
  double setPoint;
  pidGains gains;
};
