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
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");

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
    if (request->method() == HTTP_OPTIONS)
    {
      request->send(200);
    }
    else
    {
      this->handleNotFound(request);
    }
  });

  server->begin();
  Serial.println("Web server started!");
}

void FireServer::update() {}

void FireServer::handleGetStatus(AsyncWebServerRequest *request)
{
  AsyncJsonResponse *response = new AsyncJsonResponse();
  JsonObject responseBody = response->getRoot();

  responseBody["temperature"] = thermostat->temperature;
  responseBody["setPoint"] = thermostat->setPoint;
  responseBody["blowerLevel"] = blower->level;
  responseBody["batteryLevel"] = power->getBatteryLevel();
  responseBody["wifiConfigured"] = network->clientConfigured;
  responseBody["wifiConnected"] = network->wifiClientOnline;

  response->setLength();
  request->send(response);
}

void FireServer::handleGetWifiConfig(AsyncWebServerRequest *request)
{
  AsyncJsonResponse *response = new AsyncJsonResponse();
  JsonObject responseBody = response->getRoot();

  if (network->clientConfigured)
  {
    responseBody["host"] = this->network->config.host;
    responseBody["ssid"] = this->network->config.ssid;
    responseBody["password"] = strlen(this->network->config.password) > 0;
  }
  else
  {
    responseBody["host"] = "";
    responseBody["ssid"] = "";
    responseBody["password"] = false;
  }

  response->setLength();
  request->send(response);
}

void FireServer::handleSetWifiConfig(AsyncWebServerRequest *request, JsonVariant jsonBody)
{
  JsonObject requestObject = jsonBody.as<JsonObject>();
  AsyncJsonResponse *response = new AsyncJsonResponse();
  JsonObject responseBody = response->getRoot();

  if (measureJson(requestObject) > parser->wifiConfigSize)
  {
    response->setCode(413);
    responseBody["updated"] = false;
    responseBody["error"] = true;
    responseBody["message"] = "Request body too large.";
  }
  else
  {
    DynamicJsonDocument config(parser->wifiConfigSize);
    wifiConfig parsedConfig = parser->castWifiConfig(requestObject);
    config["host"] = parsedConfig.host;
    config["ssid"] = parsedConfig.ssid;
    config["password"] = parsedConfig.password;
    String newConfig = "";
    serializeJson(config, newConfig);

    if (filesystem->setWifiConfig(newConfig))
    {
      power->shouldRestart();
      responseBody["updated"] = true;
      responseBody["error"] = false;
      responseBody["message"] = "WiFi settings saved.";
    }
    else
    {
      response->setCode(500);
      responseBody["updated"] = false;
      responseBody["error"] = true;
      responseBody["message"] = "Unable to save WiFi settings.";
    }
  }

  response->setLength();
  request->send(response);
}

void FireServer::handleGetThermostatSetPoint(AsyncWebServerRequest *request)
{
  AsyncJsonResponse *response = new AsyncJsonResponse();
  JsonObject responseBody = response->getRoot();

  responseBody["setPoint"] = this->thermostat->setPoint;

  response->setLength();
  request->send(response);
}

void FireServer::handleSetThermostatSetPoint(AsyncWebServerRequest *request, JsonVariant jsonBody)
{
  JsonObject requestObject = jsonBody.as<JsonObject>();
  double newSetPoint = requestObject["setPoint"];
  AsyncJsonResponse *response = new AsyncJsonResponse();
  JsonObject responseBody = response->getRoot();

  if (newSetPoint < 150)
  {
    response->setCode(422);
    responseBody["updated"] = false;
    responseBody["error"] = true;
    responseBody["message"] = "Set point must be a number greater than 150.";
  }
  else if (newSetPoint == this->thermostat->setPoint)
  {
    responseBody["updated"] = false;
    responseBody["error"] = false;
    responseBody["message"] = "Set point not updated.";
  }
  else
  {
    responseBody["updated"] = true;
    responseBody["error"] = false;
    responseBody["message"] = "Set point updated.";
    this->thermostat->setPoint = newSetPoint;
    this->thermostat->saveConfig();
  }

  response->setLength();
  request->send(response);
}

void FireServer::handleNotFound(AsyncWebServerRequest *request)
{
  String path = request->url();
  String responseBody = "File Not Found\n\n";
  responseBody += "URL: ";
  responseBody += request->url();
  responseBody += "\nMethod: ";
  responseBody += (request->method() == HTTP_GET) ? "GET" : "POST";
  responseBody += "\nArguments: ";
  responseBody += request->args();
  responseBody += "\n";
  for (uint8_t i = 0; i < request->args(); i++)
  {
    responseBody += " " + request->argName(i) + ": " + request->arg(i) + "\n";
  }

  request->send(404, "text/plain", responseBody);
}
