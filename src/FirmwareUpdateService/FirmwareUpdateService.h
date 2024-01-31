#pragma once
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>

#include "../common/interfaces/Awaitable/Awaitable.h"

#include "model.h"

class FirmwareUpdateService : public Awaitable
{
public:
  FirmwareUpdateService(FirmwareUpdateServiceParams initParams);
  void connect();
  bool isConnected();
  void update(String firmwarePath);

private:
  struct FirmwareUpdateServiceParams params;
};