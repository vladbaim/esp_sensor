#pragma once
#include <Arduino.h>

#include "../common/interfaces/Awaitable/Awaitable.h"

#include "model.h"

class TempSensor : public Awaitable
{
public:
  virtual void connect();
  virtual void setup();
  virtual TempData getData() = 0;
};