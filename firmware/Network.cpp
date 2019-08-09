#include "Network.hpp"

void Network::init(FileSystem *filesystem)
{
  this->filesystem = filesystem;
  startWiFi();
  startmDNS();
}

void Network::update()
{
  if (!wifiOnline)
    return;

  if (mDNSOnline)
  {
    MDNS.update();
  }
  else
  {
    startmDNS();
  }
}

bool Network::online()
{
  return wifiOnline && mDNSOnline;
}

void Network::startWiFi()
{
  WiFi.mode(WIFI_STA);
  WiFi.hostname(HOSTNAME);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  Serial.print("Trying to connect to WiFi: ");
  Serial.println(WIFI_SSID);
  Serial.print("Connecting");

  for (int i = 0; WiFi.status() != WL_CONNECTED || i <= maxConnectDelays; i++)
  {
    Serial.print(".");
    delay(connectDelay);
  }

  this->wifiOnline = WiFi.status() == WL_CONNECTED;
  if (wifiOnline)
  {
    Serial.println(" Connected!");
    Serial.print("Device IP address: ");
    Serial.println(WiFi.localIP());
  }
  else
  {
    Serial.println(" Failed!");
  }
}
void Network::startmDNS()
{
  if (!wifiOnline)
    return;

  this->mDNSOnline = MDNS.begin(HOSTNAME);
  if (mDNSOnline)
  {
    Serial.println("Started mDNS.");
  }
  else
  {
    Serial.println("Unable to start mDNS.");
  }
}
