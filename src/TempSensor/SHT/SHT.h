#pragma once
#include <Arduino.h>
#include <Adafruit_SHT4x.h>
#include "../TempSensor.h"

class SHTTempSensor : public TempSensor
{
public:
  bool isConnected();
  void setup();
  TempData getData();

private:
  Adafruit_SHT4x sht4 = Adafruit_SHT4x();
};

extern SHTTempSensor shtTempSensor;