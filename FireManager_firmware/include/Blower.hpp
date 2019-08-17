#pragma once
#include <Arduino.h>

class Blower
{
public:
  Blower(byte);
  void init();
  void update();
  const byte min = 0;
  const byte max = 255;
  byte level = 0;

private:
  byte pin;
  const byte channel = 0;
  const int frequecy = 5000;
  const byte resolution = 8;
};
