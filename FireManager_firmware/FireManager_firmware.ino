#include "FireManager.hpp"

const byte powerPin = 1;
const byte thermoSKCpin = 13;
const byte thermoCSpin = 12;
const byte thermoSOpin = 14;
const byte blowerPin = 5;
const byte ledPin = 21;

Power power = Power(powerPin);
FileSystem filesystem = FileSystem();
Parser parser = Parser();
Thermostat thermostat = Thermostat(thermoSKCpin, thermoCSpin, thermoSOpin);
Blower blower = Blower(blowerPin);
Network network = Network(ledPin);
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
  blower.init();
  thermostat.init(&filesystem, &parser, &blower);
  network.init(&power, &filesystem, &parser);
  server.init(
      &power,
      &filesystem,
      &network,
      &parser,
      &thermostat,
      &blower);

  Serial.println("FireManager Booted.");
}

void loop()
{
  thermostat.update();
  blower.update();
  network.update();
  server.update();
  power.update();
}
