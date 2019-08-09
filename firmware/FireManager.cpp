#include "FireManager.hpp"

FireManager::FireManager(
    Power *power,
    FileSystem *filesystem,
    Thermometer *thermometer,
    Network *network)
{
  this->power = power;
  this->filesystem = filesystem;
  this->thermometer = thermometer;
  this->network = network;
}

void FireManager::init()
{
  power->init();
  filesystem->init();
  thermometer->init();
  network->init(filesystem);

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
  power->update();
  delay(updateDelay);
}

void FireManager::detect() {}
