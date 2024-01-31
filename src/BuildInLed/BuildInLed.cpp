#include "BuildInLed.h"

void BuildInLed::setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  off();
}

void BuildInLed::on()
{
  digitalWrite(LED_BUILTIN, LOW);
}

void BuildInLed::off()
{
  digitalWrite(LED_BUILTIN, HIGH);
}

BuildInLed buildInLed = BuildInLed();