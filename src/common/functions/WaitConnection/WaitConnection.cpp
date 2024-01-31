#include "WaitConnection.h"

void waitConnection(Awaitable *a, Blinkable *b, int blinkTimes)
{
  a->connect();
  while (!a->isConnected())
  {
    for (int i = 0; i < blinkTimes; i++)
    {
      b->blink(100);
      if (blinkTimes > 1)
      {
        delay(50);
      }
    }
    Serial.print(".");
    delay(300);
  }
  Serial.println("");
}