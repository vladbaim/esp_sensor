#include "RTCMemory.h"

uint32_t RTCMemory::getBootCount()
{
  uint32_t rtcUint = 0;
  if (!ESP.rtcUserMemoryRead(sizeof(uint32_t) * 3, &rtcUint, sizeof(uint32_t)))
  {
    Serial.println("RTC read failed!");
    while (1)
      yield();
  }

  return rtcUint;
}

void RTCMemory::saveBootCount(uint32_t bootCount)
{
  if (!ESP.rtcUserMemoryWrite(sizeof(uint32_t) * 3, &bootCount, sizeof(uint32_t)))
  {
    Serial.println("RTC write failed!");
    while (1)
      yield();
  }
}

RTCData RTCMemory::getData()
{
  RTCData rtcData;

  uint32_t rtcUint = 0;
  if (!ESP.rtcUserMemoryRead(0, &rtcUint, sizeof(uint32_t)))
  {
    Serial.println("RTC read failed!");
    while (1)
      yield();
  }
  memcpy(&rtcData.temperature, &rtcUint, sizeof(float));

  rtcUint = 0;
  if (!ESP.rtcUserMemoryRead(sizeof(uint32_t), &rtcUint, sizeof(uint32_t)))
  {
    Serial.println("RTC read failed!");
    while (1)
      yield();
  }
  memcpy(&rtcData.humidity, &rtcUint, sizeof(float));

  rtcUint = 0;
  if (!ESP.rtcUserMemoryRead(sizeof(uint32_t) * 2, &rtcUint, sizeof(uint32_t)))
  {
    Serial.println("RTC read failed!");
    while (1)
      yield();
  }
  rtcData.carbonDioxide = (int)rtcUint;

  return rtcData;
}

void RTCMemory::saveData(RTCData rtcData)
{
  uint32_t rtcUint = 0;
  memcpy(&rtcUint, &rtcData.temperature, sizeof(uint32_t));
  if (!ESP.rtcUserMemoryWrite(0, &rtcUint, sizeof(uint32_t)))
  {
    Serial.println("RTC write failed!");
    while (1)
      yield();
  }

  rtcUint = 0;
  memcpy(&rtcUint, &rtcData.humidity, sizeof(uint32_t));
  if (!ESP.rtcUserMemoryWrite(sizeof(uint32_t), &rtcUint, sizeof(uint32_t)))
  {
    Serial.println("RTC write failed!");
    while (1)
      yield();
  }

  rtcUint = (uint32_t)rtcData.carbonDioxide;
  memcpy(&rtcUint, &rtcUint, sizeof(uint32_t));
  if (!ESP.rtcUserMemoryWrite(sizeof(uint32_t) * 2, &rtcUint, sizeof(uint32_t)))
  {
    Serial.println("RTC write failed!");
    while (1)
      yield();
  }
}

RTCMemory rtcMemory = RTCMemory();