// Project includes
#include "globals.h"
#include "power.h"
#include "networking.h"
#include <max6675.h>

int ktcSO = D6;
int ktcCS = D7;
int ktcCLK = D5;

MAX6675 ktc(ktcCLK, ktcCS, ktcSO);

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println("");
  Serial.println("Booted.");

  setupPower();
  setupNetworking();

  delay(500);
}

void loop()
{
  Serial.print("C = ");
  Serial.println(ktc.readCelsius());
  delay(1000);
}
