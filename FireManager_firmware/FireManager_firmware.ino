#include "include/Power.hpp"
#include "include/FileSystem.hpp"
#include "include/Parser.hpp"
#include "include/Thermometer.hpp"
#include "include/Network.hpp"
#include "include/FireServer.hpp"

Power power = Power(1);
FileSystem filesystem = FileSystem();
Parser parser = Parser();
Thermometer thermometer = Thermometer(13, 12, 14);
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
  network.init(&filesystem, &parser);
  server.init(&filesystem, &network, &parser, &thermometer);
  Serial.println("FireManager Booted.");
}

void loop()
{
  thermometer.update();
  network.update();
  server.update();
  power.update();
}
