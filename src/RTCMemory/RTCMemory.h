#pragma once
#include <Arduino.h>
#include "./model.h"

class RTCMemory
{
public:
  uint32_t getBootCount();
  void saveBootCount(uint32_t bootCount);
  RTCData getData();
  void saveData(RTCData rtcData);
};

extern RTCMemory rtcMemory;