#include "networking.h"

bool mdns = false;

void setupNetworking()
{
  WiFi.mode(WIFI_STA);
  WiFi.hostname(HOSTNAME);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  Serial.print("Trying to connect to WiFi: ");
  Serial.println(WIFI_SSID);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(250);
    Serial.print(".");
  }

  Serial.println(" Connected!");
  Serial.print("Device IP address: ");
  Serial.println(WiFi.localIP());

  if (mDNS())
  {
    Serial.println("Network ready.");
  }
  else
  {
    Serial.print("Connected to WiFi, ");
    Serial.print("but unable to start mDNS, ");
    Serial.println("going to sleep.");
    forceNapIf(true);
  }
}

bool mDNS()
{
  if (!mdns)
  {
    mdns = MDNS.begin(HOSTNAME);
    if (!mdns)
      Serial.println("mDNS responder error!");
  }
  return mdns;
}
