#include "FireServer.hpp"

void FireServer::init()
{
  this->server = new ESP8266WebServer(serverPort);

  server->on("/", [this]() {
    this->handleRoot();
  });
  server->onNotFound([this]() {
    this->handleNotFound();
  });

  server->begin();
}

void FireServer::update()
{
  server->handleClient();
}

void FireServer::handleRoot()
{
  server->send(200, "text/plain", "Hello from FireManager!");
}

void FireServer::handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server->uri();
  message += "\nMethod: ";
  message += (server->method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server->args();
  message += "\n";
  for (uint8_t i = 0; i < server->args(); i++)
  {
    message += " " + server->argName(i) + ": " + server->arg(i) + "\n";
  }
  server->send(404, "text/plain", message);
}
