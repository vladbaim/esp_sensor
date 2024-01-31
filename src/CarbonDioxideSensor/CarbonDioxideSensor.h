#pragma once
#include <Arduino.h>
#include <SoftwareSerial.h>

#define RX_PIN 13
#define TX_PIN 15
#define BAUDRATE 9600

class CarbonDioxideSensor
{
public:
  void setup();
  int getCarbonDioxide();
};

extern CarbonDioxideSensor carbonDioxideSensor;