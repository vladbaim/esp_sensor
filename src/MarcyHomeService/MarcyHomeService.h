#pragma once
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#include "../common/interfaces/Awaitable/Awaitable.h"

#include "model.h"

class MarcyHomeService : public Awaitable
{
public:
  MarcyHomeService(MarcyHomeServiceParams initParams);
  void connect();
  bool isConnected();
  String getIp();
  void setSensorData(SensorData data);
  String getNewFirmware();

private:
  struct MarcyHomeServiceParams params;
};