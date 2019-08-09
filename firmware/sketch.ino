#include "FireManager.hpp"

Power power = Power(D0);
FileSystem filesystem = FileSystem();
Parser parser = Parser();
Thermometer thermometer = Thermometer(D5, D7, D6);
Network network = Network();
FireServer server = FireServer();

FireManager firemanager = FireManager(
    &power,
    &filesystem,
    &parser,
    &thermometer,
    &network,
    &server);

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
