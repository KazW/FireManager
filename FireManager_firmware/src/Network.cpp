#include "../include/Network.hpp"

void Network::init(FileSystem *filesystem, Parser *parser)
{
  this->filesystem = filesystem;
  this->parser = parser;
  this->clientConfigured = filesystem->wifiClientConfigured();
  WiFi.mode(WIFI_AP_STA);
  startWiFiAp();
  startWiFiClient();
  startmDNS();
}

void Network::update()
{
  if (clientConfigured && !wifiClientOnline && WiFi.status() == WL_CONNECTED)
  {
    this->wifiClientOnline = true;
    Serial.print("WiFi Connected to: ");
    Serial.println(config.ssid);
    Serial.print("Device IP address: ");
    Serial.println(WiFi.localIP());
  }

  if (!wifiApOnline)
    startWiFiAp();

  if (!mDNSOnline)
    startmDNS();
}

bool Network::wifiClient()
{
  return clientConfigured;
}

void Network::startWiFiAp()
{
  WiFi.softAPsetHostname(apHost);
  WiFi.softAPConfig(apIP, apGateway, apSubnet);
  this->wifiApOnline = WiFi.softAP(apSSID, apPassword);

  if (wifiApOnline)
    Serial.println("WiFi AP started!");
  else
    Serial.println("WiFi AP failed to start!");
}

void Network::startWiFiClient()
{
  if (!clientConfigured)
    return;

  this->config = this->parser->parseAndCastWifiConfig(
      this->filesystem->getWifiConfig());
  this->hostname = config.host;

  WiFi.setHostname(hostname);
  WiFi.begin(config.ssid, config.password);

  Serial.print("Trying to connect to WiFi: ");
  Serial.println(config.ssid);
}

void Network::startmDNS()
{
  if (!wifiClientOnline)
    return;

  this->mDNSOnline = MDNS.begin(hostname);
  if (mDNSOnline)
    Serial.println("Started mDNS.");
  else
    Serial.println("Unable to start mDNS.");
}
