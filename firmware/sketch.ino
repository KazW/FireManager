#include "FireManager.hpp"

Power power = Power(D0);
Thermometer thermometer = Thermometer(D5, D7, D6);
Network network = Network();

FireManager fireManager = FireManager(&power, &thermometer, &network);

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println("");
  Serial.println("Booted.");

  fireManager.init();
}

void loop()
{
  fireManager.update();
}
