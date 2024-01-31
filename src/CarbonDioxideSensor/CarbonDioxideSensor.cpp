#include "CarbonDioxideSensor.h"

SoftwareSerial co2Serial(RX_PIN, TX_PIN);

void CarbonDioxideSensor::setup()
{
  co2Serial.begin(BAUDRATE);
}

byte getCheckSum(char *packet)
{
  byte i;
  unsigned char checksum = 0;
  for (i = 1; i < 8; i++)
  {
    checksum += packet[i];
  }
  checksum = 0xff - checksum;
  checksum += 1;
  return checksum;
}

int CarbonDioxideSensor::getCarbonDioxide()
{
  byte cmd[9] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
  char response[9];
  co2Serial.write(cmd, 9);
  memset(response, 0, 9);
  int i = 0;
  while (co2Serial.available() == 0)
  {
    delay(1000);
    i++;
  }
  if (co2Serial.available() > 0)
  {
    co2Serial.readBytes(response, 9);
  }
  byte check = getCheckSum(response);
  if (response[8] != check)
  {
    Serial.println("Checksum not OK!");
    Serial.print("Received: ");
    Serial.println(response[8]);
    Serial.print("Should be: ");
    Serial.println(check);
    byte crc[9] = {};
    return 0;
  }

  int ppm_uart = 256 * (int)response[2] + response[3];
  byte crc[9] = {};
  if (ppm_uart == 500)
  {
    return 0;
  }
  return ppm_uart;
}

CarbonDioxideSensor carbonDioxideSensor = CarbonDioxideSensor();