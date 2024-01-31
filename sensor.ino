#include "./settings.h"

#include "src/common/functions/WaitConnection/WaitConnection.h"
#include "src/BuildInLed/BuildInLed.h"
#include "src/TempSensor/index.h"
#include "src/CarbonDioxideSensor/CarbonDioxideSensor.h"
#include "src/MarcyHomeService/MarcyHomeService.h"
#include "src/NullSerial/NullSerial.h"
#include "src/RTCMemory/RTCMemory.h"
#include "src/FirmwareUpdateService/FirmwareUpdateService.h"

MarcyHomeService marcyHomeService({WIFI_NAME,
                                   WIFI_PASSWORD,
                                   API_PATH,
                                   SENSOR_POSITION,
                                   VERSION});

FirmwareUpdateService firmwareUpdateService({
    WIFI_NAME,
    WIFI_PASSWORD,
    SERVER_PATH,
});

void setup()
{
#if DEBUG
  Serial.begin(SERIAL_BAUDRATE);
  while (!Serial)
  {
  }
  Serial.println("");
#endif
  uint32_t bootCount = rtcMemory.getBootCount();
  Serial.println(START_MESSAGE);
  Serial.println("VERSION");
  Serial.println(VERSION);
  Serial.println("bootCount");
  Serial.println(bootCount);
  bootCount++;

  buildInLed.setup();

  if (bootCount > BOOT_COUNT_UPDATE)
  {
    rtcMemory.saveBootCount(0);
    update();
  }
  else
  {
    rtcMemory.saveBootCount(bootCount);
  }

  check();

  delay(100);
  ESP.deepSleep(SLEEP_TIME);
}

void check()
{
  carbonDioxideSensor.setup();

  waitConnection(&tempSensor, &buildInLed, 1);

  RTCData savedRTCData = rtcMemory.getData();
  Serial.println("savedRTCData");
  Serial.println(savedRTCData.temperature);
  Serial.println(savedRTCData.humidity);
  Serial.println(savedRTCData.carbonDioxide);

  int carbonDioxide = carbonDioxideSensor.getCarbonDioxide();
  if (carbonDioxide == 0)
  {
    return;
  }
  TempData tempData = tempSensor.getData();

  Serial.println("newSensorsData");
  Serial.println(tempData.temperature);
  Serial.println(tempData.humidity);
  Serial.println(carbonDioxide);

  if (savedRTCData.temperature - tempData.temperature > TEMPERATURE_DIFF ||
      savedRTCData.temperature - tempData.temperature < -TEMPERATURE_DIFF ||
      savedRTCData.humidity - tempData.humidity > HUMIDITY_DIFF ||
      savedRTCData.humidity - tempData.humidity < -HUMIDITY_DIFF ||
      savedRTCData.carbonDioxide - carbonDioxide > CARBON_DIOXIDE_DIFF ||
      savedRTCData.carbonDioxide - carbonDioxide < -CARBON_DIOXIDE_DIFF)
  {
    waitConnection(&marcyHomeService, &buildInLed, 2);
    SensorData sensorData;
    sensorData.temperature = tempData.temperature;
    sensorData.humidity = tempData.humidity;
    sensorData.carbonDioxide = carbonDioxide;

    marcyHomeService.setSensorData(sensorData);

    RTCData rtcData;
    rtcData.temperature = tempData.temperature;
    rtcData.humidity = tempData.humidity;
    rtcData.carbonDioxide = carbonDioxide;
    rtcMemory.saveData(rtcData);
  }
}

void update()
{
  waitConnection(&marcyHomeService, &buildInLed, 2);
  String path = marcyHomeService.getNewFirmware();
  Serial.println("marcyHomeService path: ");
  Serial.println(path);

  if (path == "")
  {
    return;
  }

  waitConnection(&firmwareUpdateService, &buildInLed, 2);
  firmwareUpdateService.update(path);
}

void loop()
{
}