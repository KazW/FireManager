#include "FireManager.hpp"

Power power = Power(D0);
FileSystem filesystem = FileSystem();
Thermometer thermometer = Thermometer(D5, D7, D6);
Network network = Network();

FireManager firemanager = FireManager(
    &power,
    &filesystem,
    &thermometer,
    &network);

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println("");
  Serial.println("Booted.");

  firemanager.init();
}

void loop()
{
  firemanager.update();
}
