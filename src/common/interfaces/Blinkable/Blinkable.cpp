#include "Blinkable.h"

void Blinkable::blink(int time)
{
  on();
  delay(time);
  off();
}