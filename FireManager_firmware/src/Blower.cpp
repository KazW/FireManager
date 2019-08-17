#include "../include/Blower.hpp"

Blower::Blower(byte pin) { this->pin = pin; }

void Blower::init()
{
  ledcSetup(channel, frequecy, resolution);
  ledcAttachPin(pin, channel);
  ledcWrite(channel, level);
}

void Blower::update()
{
  ledcWrite(channel, level);
}
