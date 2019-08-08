#include "FireManager.hpp"

FireManager::FireManager(Power *power, Thermometer *thermometer, Network *network)
{
  this->power = power;
  this->thermometer = thermometer;
  this->network = network;
}

void FireManager::init()
{
  power->init();
  thermometer->init();
  network->init();

  verify();
}

void FireManager::verify()
{
  if (power->batteryVoltage() <= lowBatteryVoltage)
  {
    // audio->ping();
    // audio->ping();
    // TODO flash LEDs
    power->sleepNow(300 * 1e6); // Sleep for 5 minutes
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
}

void FireManager::detect() {}
