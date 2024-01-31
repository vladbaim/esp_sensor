#include "AHT.h"

bool AHTTempSensor::isConnected()
{
  return !!_aht.begin();
}

TempData AHTTempSensor::getData()
{
  TempData data;

  sensors_event_t humidity, temp;

  _aht.getEvent(&humidity, &temp);
  data.temperature = temp.temperature;
  data.humidity = humidity.relative_humidity;

  return data;
}

AHTTempSensor ahtTempSensor = AHTTempSensor();