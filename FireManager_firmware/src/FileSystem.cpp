#include "../include/FileSystem.hpp"

void FileSystem::init()
{
  SPIFFS.begin(true);

  if (!exists(configDir))
    SPIFFS.mkdir(configDir);

  if (!exists(webDir))
    SPIFFS.mkdir(webDir);
}

bool FileSystem::exists(char *fileName)
{
  return SPIFFS.exists(fileName);
}

bool FileSystem::exists(const char *fileName)
{
  return SPIFFS.exists(fileName);
}

String FileSystem::readFile(String fileName)
{
  File file = SPIFFS.open(fileName, "r");
  String contents = file.readString();
  file.close();
  return contents;
}

bool FileSystem::writeFile(String fileName, String contents)
{
  File file = SPIFFS.open(fileName, "w");
  bool result;
  if (file.print(contents))
  {
    result = true;
  }
  else
  {
    result = false;
  }
  file.close();
  return result;
}

bool FileSystem::wifiClientConfigured()
{
  return exists(wifiConfigFile);
}

String FileSystem::getWifiConfig()
{
  return readFile(wifiConfigFile);
}

bool FileSystem::setWifiConfig(String newConfig)
{
  return writeFile(wifiConfigFile, newConfig);
}

bool FileSystem::thermostatConfigured()
{
  return exists(thermostatConfigFile);
}

String FileSystem::getThermostatConfig()
{
  return readFile(thermostatConfigFile);
}

bool FileSystem::setThermostatConfig(String newConfig)
{
  return writeFile(thermostatConfigFile, newConfig);
}
