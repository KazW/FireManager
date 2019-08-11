#include "FireServer.hpp"

void FireServer::init(FileSystem *filesystem, Network *network, Parser *parser)
{
  this->filesystem = filesystem;
  this->network = network;
  this->parser = parser;
  this->server = new ESP8266WebServer(serverPort);

  server->on("/api/wifi", [this]() {
    if (server->method() == HTTP_GET)
    {
      this->handleGetWifiConfig();
    }
    else if (server->method() == HTTP_POST)
    {
      this->handleSetWifiConfig();
    }
    else
    {
      this->handleNotFound();
    }
  });
  server->onNotFound([this]() {
    this->handleNotFound();
  });
}

void FireServer::update()
{
  if (!serverStarted && network->online())
  {
    server->begin();
    this->serverStarted = true;
    Serial.println("Web server started!");
  }
  else if (serverStarted)
  {
    server->handleClient();
  }
}

void FireServer::handleSetWifiConfig()
{
  String rawConfig = server->arg("plain");
  const int responseCapacity = JSON_OBJECT_SIZE(2) + 90;
  DynamicJsonDocument responseBuffer(responseCapacity);
  String response = "";

  if (rawConfig.length() > parser->getwifiConfigSize())
  {
    responseBuffer["error"] = true;
    responseBuffer["message"] = "request body too large";
    serializeJson(responseBuffer, response);
    server->sendHeader("Content-Length", String(response.length()));
    server->send(413, "application/json", response);
    return;
  }

  wifiConfig parsedConfig = parser->parseAndCastWifiConfig(rawConfig);
  ArduinoJson6113_00000::DynamicJsonDocument config = parser->getWifiConfigBuffer();
  config["host"] = parsedConfig.host;
  config["ssid"] = parsedConfig.ssid;
  config["password"] = parsedConfig.password;
  String newConfig = "";
  serializeJson(config, newConfig);

  if (filesystem->setWifiConfig(newConfig))
  {
    server->send(202);
  }
  else
  {
    responseBuffer["error"] = true;
    responseBuffer["message"] = "unable to save config";
    serializeJson(responseBuffer, response);
    server->sendHeader("Content-Length", String(response.length()));
    server->send(500, "application/json", response);
  }
}

void FireServer::handleGetWifiConfig()
{
  ArduinoJson6113_00000::DynamicJsonDocument config = parser->getWifiConfigBuffer();
  if (filesystem->wifiConfigured())
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

  String message = "";
  serializeJson(config, message);
  server->sendHeader("Content-Length", String(message.length()));
  server->send(200, "application/json", message);
}

void FireServer::handleNotFound()
{
  String path = server->uri();
  if (handleFileRead(path))
    return;

  Serial.println(String("Serving not found page for: ") + path);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += path;
  message += "\nMethod: ";
  message += (server->method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server->args();
  message += "\n";
  for (uint8_t i = 0; i < server->args(); i++)
  {
    message += " " + server->argName(i) + ": " + server->arg(i) + "\n";
  }

  server->sendHeader("Content-Length", String(message.length()));
  server->send(404, "text/plain", message);
}

bool FireServer::handleFileRead(String path)
{
  path = filesystem->getWebDir() + path;
  Serial.println("handleFileRead: " + path);
  if (path.endsWith("/"))
    path += "index.html";
  String contentType = getContentType(&path);
  String pathWithGz = path + ".gz";
  if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path))
  {
    if (SPIFFS.exists(pathWithGz))
    {
      path += ".gz";
      server->sendHeader("Content-Encoding", "gzip");
    };
    File file = SPIFFS.open(path, "r");
    server->sendHeader("Content-Length", String(file.size()));
    size_t sent = server->streamFile(file, contentType);
    file.close();
    Serial.println(String("\tSent file: ") + path);
    return true;
  }
  Serial.println(String("\tFile Not Found: ") + path);
  return false;
}

String FireServer::getContentType(String *filename)
{
  if (filename->endsWith(".htm"))
    return "text/html";
  else if (filename->endsWith(".html"))
    return "text/html";
  else if (filename->endsWith(".css"))
    return "text/css";
  else if (filename->endsWith(".js"))
    return "application/javascript";
  else if (filename->endsWith(".png"))
    return "image/png";
  else if (filename->endsWith(".gif"))
    return "image/gif";
  else if (filename->endsWith(".jpg"))
    return "image/jpeg";
  else if (filename->endsWith(".ico"))
    return "image/x-icon";
  else if (filename->endsWith(".xml"))
    return "text/xml";
  else if (filename->endsWith(".pdf"))
    return "application/x-pdf";
  else if (filename->endsWith(".zip"))
    return "application/x-zip";
  else if (filename->endsWith(".gz"))
    return "application/x-gzip";
  return "text/plain";
}
