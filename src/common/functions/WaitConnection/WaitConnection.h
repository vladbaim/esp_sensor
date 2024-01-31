#pragma once
#include <Arduino.h>

#include "../../interfaces/Awaitable/Awaitable.h"
#include "../../interfaces/Blinkable/Blinkable.h"

void waitConnection(Awaitable *a, Blinkable *b, int blinkTimes);
