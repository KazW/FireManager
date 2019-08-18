#include "../include/FireServer.hpp"

void FireServer::init(
    Power *power,
    FileSystem *filesystem,
    Network *network,
    Parser *parser,
    Thermostat *thermostat,
    Blower *blower)
{
  this->power = power;
  this->filesystem = filesystem;
  this->network = network;
  this->parser = parser;
  this->thermostat = thermostat;
  this->blower = blower;
  this->server = new AsyncWebServer(serverPort);

  DefaultHeaders::Instance().addHeader("Server", "FireServer 0.1");
  server->serveStatic("/", SPIFFS, filesystem->webDir)
      .setDefaultFile("index.html");

  server->on("/api/status", HTTP_GET, [this](AsyncWebServerRequest *request) {
    this->handleGetStatus(request);
  });

  server->on("/api/wifi", HTTP_GET, [this](AsyncWebServerRequest *request) {
    this->handleGetWifiConfig(request);
  });

  AsyncCallbackJsonWebHandler *setWifiHandler = new AsyncCallbackJsonWebHandler("/api/wifi", [this](AsyncWebServerRequest *request, JsonVariant &json) {
    this->handleSetWifiConfig(request, json);
  });
  server->addHandler(setWifiHandler);

  server->on("/api/set-point", HTTP_GET, [this](AsyncWebServerRequest *request) {
    this->handleGetThermostatSetPoint(request);
  });

  AsyncCallbackJsonWebHandler *setThermostatSetPointHandler = new AsyncCallbackJsonWebHandler("/api/set-point", [this](AsyncWebServerRequest *request, JsonVariant &json) {
    this->handleSetThermostatSetPoint(request, json);
  });
  server->addHandler(setThermostatSetPointHandler);

  server->onNotFound([this](AsyncWebServerRequest *request) {
    this->handleNotFound(request);
  });

  server->begin();
  Serial.println("Web server started!");
}

void FireServer::update() {}

void FireServer::handleGetStatus(AsyncWebServerRequest *request)
{
  String response = "";
  DynamicJsonDocument responseBuffer(JSON_OBJECT_SIZE(6) + 171);

  responseBuffer["temperature"] = thermostat->temperature;
  responseBuffer["setPoint"] = thermostat->setPoint;
  responseBuffer["blowerLevel"] = blower->level;
  responseBuffer["batteryLevel"] = power->getBatteryLevel();
  responseBuffer["wifiConfigured"] = network->clientConfigured;
  responseBuffer["wifiConnected"] = network->wifiClientOnline;

  serializeJson(responseBuffer, response);
  request->send(200, "application/json", response);
}

void FireServer::handleGetWifiConfig(AsyncWebServerRequest *request)
{
  String response = "";
  DynamicJsonDocument config = parser->getWifiConfigBuffer();

  if (filesystem->wifiClientConfigured())
  {
    deserializeJson(config, filesystem->getWifiConfig());
    String password = config["password"];
    config["password"] = password.length() > 0;
  }
  else
  {
    config["host"] = "";
    config["ssid"] = "";
    config["password"] = false;
  }

  serializeJson(config, response);
  request->send(200, "application/json", response);
}

void FireServer::handleSetWifiConfig(AsyncWebServerRequest *request, JsonVariant jsonBody)
{
  String rawConfig = "";
  serializeJson(jsonBody, rawConfig);
  Serial.print("Got wifi config post from handler: ");
  serializeJson(jsonBody, Serial);
  Serial.println("");
  const int responseCapacity = JSON_OBJECT_SIZE(2) + 90;
  DynamicJsonDocument responseBuffer(responseCapacity);
  String response = "";

  if (rawConfig.length() > parser->wifiConfigSize)
  {
    responseBuffer["error"] = true;
    responseBuffer["message"] = "request body too large";
    serializeJson(responseBuffer, response);
    request->send(413, "application/json", response);
    return;
  }

  DynamicJsonDocument config(parser->wifiConfigSize);
  wifiConfig parsedConfig = parser->parseAndCastWifiConfig(rawConfig);
  config["host"] = parsedConfig.host;
  config["ssid"] = parsedConfig.ssid;
  config["password"] = parsedConfig.password;
  String newConfig = "";
  serializeJson(config, newConfig);
  Serial.println("Cleaned wifi config: " + newConfig);

  if (filesystem->setWifiConfig(newConfig))
  {
    power->shouldRestart();
    request->send(202);
  }
  else
  {
    responseBuffer["error"] = true;
    responseBuffer["message"] = "unable to save config";
    serializeJson(responseBuffer, response);
    request->send(500, "application/json", response);
  }
}

void FireServer::handleGetThermostatSetPoint(AsyncWebServerRequest *request)
{
  const int capacity = JSON_OBJECT_SIZE(1) + 25;
  DynamicJsonDocument doc(capacity);

  doc["setPoint"] = this->thermostat->setPoint;

  AsyncResponseStream *response = request->beginResponseStream("application/json");
  serializeJson(doc, *response);
  request->send(response);
}

void FireServer::handleSetThermostatSetPoint(AsyncWebServerRequest *request, JsonVariant jsonBody)
{
  JsonObject jsonBodyObject = jsonBody.as<JsonObject>();
  double newSetPoint = jsonBodyObject["setPoint"] | 0;

  if (newSetPoint < 150)
  {
    const int responseCapacity = JSON_OBJECT_SIZE(2) + 90;
    DynamicJsonDocument responseBuffer(responseCapacity);
    AsyncResponseStream *response = request->beginResponseStream("application/json");

    responseBuffer["error"] = true;
    responseBuffer["message"] = "Set point must be a number greater than 150.";

    serializeJson(responseBuffer, *response);
    request->send(response);
  }
  else if (newSetPoint == this->thermostat->setPoint)
  {
    request->send(202);
  }
  else
  {
    request->send(202);
    this->thermostat->setPoint = newSetPoint;
    this->thermostat->saveConfig();
  }
}

void FireServer::handleNotFound(AsyncWebServerRequest *request)
{
  String path = request->url();
  Serial.println(String("Serving not found page for: ") + path);
  String message = "File Not Found\n\n";
  message += "URL: ";
  message += request->url();
  message += "\nMethod: ";
  message += (request->method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += request->args();
  message += "\n";
  for (uint8_t i = 0; i < request->args(); i++)
  {
    message += " " + request->argName(i) + ": " + request->arg(i) + "\n";
  }

  request->send(404, "text/plain", message);
}
