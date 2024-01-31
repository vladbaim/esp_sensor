#pragma once
#include <Arduino.h>
#include <Adafruit_AHTX0.h>
#include "../TempSensor.h"

class AHTTempSensor : public TempSensor
{
public:
  bool isConnected();
  TempData getData();

private:
  Adafruit_AHTX0 _aht;
};

extern AHTTempSensor ahtTempSensor;