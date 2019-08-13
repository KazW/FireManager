#include "../include/FireServer.hpp"

void FireServer::init(
    Power *power,
    FileSystem *filesystem,
    Network *network,
    Parser *parser,
    Thermometer *thermometer,
    Blower *blower)
{
  this->power = power;
  this->filesystem = filesystem;
  this->network = network;
  this->parser = parser;
  this->thermometer = thermometer;
  this->blower = blower;
  this->server = new AsyncWebServer(serverPort);

  DefaultHeaders::Instance().addHeader("Server", "FireServer 0.1");
  server->serveStatic("/", SPIFFS, filesystem->getWebDir())
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
  DynamicJsonDocument responseBuffer(JSON_OBJECT_SIZE(4) + 112);

  responseBuffer["temperature"] = thermometer->getTemperature();
  responseBuffer["batteryLevel"] = power->getBatteryLevel();
  responseBuffer["wifiClient"] = network->wifiClient();
  responseBuffer["blowerLevel"] = blower->getLevel();

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

  if (rawConfig.length() > parser->getwifiConfigSize())
  {
    responseBuffer["error"] = true;
    responseBuffer["message"] = "request body too large";
    serializeJson(responseBuffer, response);
    request->send(413, "application/json", response);
    return;
  }

  DynamicJsonDocument config(parser->getwifiConfigSize());
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
