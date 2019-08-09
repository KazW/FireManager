#include "Parser.hpp"

void Parser::init(FileSystem *filesystem)
{
  this->filesystem = filesystem;
}

wifiConfig Parser::parseWifiConfig()
{
  wifiConfig config;
  char *rawConfig = filesystem->getWifiConfig();
  DynamicJsonDocument data(configJSONSize);

  Serial.print("Parsing wifi config: ");
  Serial.println(rawConfig);

  deserializeJson(data, rawConfig);
  config.ssid = data["ssid"];
  config.password = data["password"];
  config.host = data["host"];

  return config;
}
