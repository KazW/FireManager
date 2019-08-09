#include "Network.hpp"

void Network::init(FileSystem *filesystem, Parser *parser)
{
  this->filesystem = filesystem;
  this->parser = parser;
  this->clientMode = filesystem->wifiConfigured();

  if (clientMode)
  {
    startWiFiClient();
  }
  else
  {
    startWiFiAp();
  }

  startmDNS();
}

void Network::update()
{
  if (clientMode && !wifiOnline && WiFi.status() == WL_CONNECTED)
  {
    this->wifiOnline = true;
    Serial.println("WiFi Connected!");
    Serial.print("Device IP address: ");
    Serial.println(WiFi.localIP());
  }

  if (!clientMode && !wifiOnline)
    startWiFiAp();

  if (mDNSOnline)
  {
    MDNS.update();
  }
  else if (wifiOnline)
  {
    startmDNS();
  }
}

bool Network::online()
{
  return wifiOnline && mDNSOnline;
}

bool Network::wifiClient()
{
  return clientMode;
}

void Network::startWiFiAp()
{
  WiFi.softAPConfig(apIP, apGateway, apSubnet);
  this->wifiOnline = WiFi.softAP(apSSID, apPassword);

  if (wifiOnline)
  {
    this->hostname = apHost;
    Serial.println("WiFi ap started!");
  }
  else
  {
    Serial.println("WiFi ap failed to start!");
  }
}

void Network::startWiFiClient()
{
  this->config = this->parser->parseWifiConfig();
  this->hostname = config.host;

  WiFi.mode(WIFI_STA);
  WiFi.hostname(hostname);
  WiFi.begin(config.ssid, config.password);

  Serial.print("Trying to connect to WiFi: ");
  Serial.println(config.ssid);
}

void Network::startmDNS()
{
  if (!wifiOnline)
    return;

  this->mDNSOnline = MDNS.begin(hostname);
  if (mDNSOnline)
  {
    Serial.println("Started mDNS.");
  }
  else
  {
    Serial.println("Unable to start mDNS.");
  }
}
