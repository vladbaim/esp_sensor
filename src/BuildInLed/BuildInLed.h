#pragma once
#include <Arduino.h>
#include "../common/interfaces/Blinkable/Blinkable.h"

class BuildInLed : public Blinkable
{
public:
  void setup();
  void on();
  void off();
};

extern BuildInLed buildInLed;