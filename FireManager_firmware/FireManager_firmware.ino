#include "FireManager.hpp"

Power power = Power(1);
FileSystem filesystem = FileSystem();
Parser parser = Parser();
Thermometer thermometer = Thermometer(13, 12, 14);
Blower blower = Blower(5);
Network network = Network();
FireServer server = FireServer();

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println("");
  Serial.println("FireManager Booting...");

  power.init();
  filesystem.init();
  thermometer.init();
  blower.init();
  network.init(&power, &filesystem, &parser);
  server.init(
      &power,
      &filesystem,
      &network,
      &parser,
      &thermometer,
      &blower);

  Serial.println("FireManager Booted.");
}

void loop()
{
  thermometer.update();
  blower.update();
  network.update();
  server.update();
  power.update();
}
