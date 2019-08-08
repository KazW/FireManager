#include "power.h"

const int sleepyTime = 10 * 1000000;

void setupPower()
{
  pinMode(D0, WAKEUP_PULLUP);
}

void forceNapIf(bool force)
{
  if (force)
    ESP.deepSleep(sleepyTime);
}
