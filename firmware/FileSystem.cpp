#include "FileSystem.hpp"

void FileSystem::init()
{
  SPIFFS.begin();
}

bool FileSystem::wifiConfigured()
{
  return SPIFFS.exists(wifiConfigFile);
}

char *FileSystem::getWifiConfig()
{
  File configFile = SPIFFS.open(wifiConfigFile, "r");
  int configSize = configFile.size();

  std::unique_ptr<char[]> buf(new char[configSize]);
  configFile.readBytes(buf.get(), configSize);
  return buf.get();
}
