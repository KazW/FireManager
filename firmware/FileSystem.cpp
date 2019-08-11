#include "FileSystem.hpp"

void FileSystem::init()
{
  SPIFFS.begin();

  if (!SPIFFS.exists(configDir))
    SPIFFS.mkdir(configDir);

  if (!SPIFFS.exists(webDir))
    SPIFFS.mkdir(webDir);
}

bool FileSystem::wifiConfigured()
{
  return SPIFFS.exists(wifiConfigFile);
}

String FileSystem::getWifiConfig()
{
  File configFile = SPIFFS.open(wifiConfigFile, "r");
  String config = configFile.readString();
  configFile.close();
  return config;
}

bool FileSystem::setWifiConfig(String newConfig)
{
  File configFile = SPIFFS.open(wifiConfigFile, "w");
  bool result;
  if (configFile.print(newConfig))
  {
    result = true;
  }
  else
  {
    result = false;
  }
  configFile.close();
  return result;
}

char *FileSystem::getWebDir()
{
  return webDir;
}
