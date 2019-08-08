#pragma once
// Network libraries
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

#include "secrets.h" // Needs to be manually created
#include "globals.h"
#include "power.h"

void setupNetworking();
bool mDNS();
