#include "FireManager.hpp"

FireManager::FireManager(
    Power *power,
    FileSystem *filesystem,
    Parser *parser,
    Thermometer *thermometer,
    Network *network,
    FireServer *server)
{
  this->power = power;
  this->filesystem = filesystem;
  this->parser = parser;
  this->thermometer = thermometer;
  this->network = network;
  this->server = server;
}

void FireManager::init()
{
  power->init();
  filesystem->init();
  parser->init(filesystem);
  thermometer->init();
  network->init(filesystem, parser);
  server->init(filesystem, network);

  verify();
}

void FireManager::verify()
{
  if (power->lowBattery())
  {
    // TODO flash LEDs
    power->sleepNow(lowBatterySleepTime);
  }
}

void FireManager::update()
{
  // Read Inputs
  thermometer->update();

  // Evaluate readings and configure outputs
  detect();

  // Update outputs
  // audio->update();
  // led->update();

  // Sleep or loop
  network->update();
  server->update();
  power->update();
}

void FireManager::detect() {}
