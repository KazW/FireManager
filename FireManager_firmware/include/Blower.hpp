#pragma once
#include <Arduino.h>

class Blower
{
public:
  Blower(byte);
  void init();
  void update();
  void setLevel(byte);
  byte getLevel();

private:
  byte pin;
  byte level = 0;

  const byte channel = 0;
  const int frequecy = 5000;
  const byte resolution = 8;
};
