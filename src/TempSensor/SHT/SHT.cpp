#include "SHT.h"

bool SHTTempSensor::isConnected()
{
  if (!!sht4.begin())
  {
    setup();
    return true;
  }

  return false;
}

void SHTTempSensor::setup()
{
  sht4.setPrecision(SHT4X_HIGH_PRECISION);
  sht4.setHeater(SHT4X_NO_HEATER);
}

TempData SHTTempSensor::getData()
{
  TempData data;

  sensors_event_t humidity, temp;

  sht4.getEvent(&humidity, &temp);
  data.temperature = temp.temperature;
  data.humidity = humidity.relative_humidity;

  return data;
}

SHTTempSensor shtTempSensor = SHTTempSensor();