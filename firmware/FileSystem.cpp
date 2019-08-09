#include "FileSystem.hpp"

void FileSystem::init()
{
  SPIFFS.begin();
}

bool FileSystem::wifiConfigured()
{
  return SPIFFS.exists(wifiConfigFile);
}
