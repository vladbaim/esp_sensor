#include "FirmwareUpdateService.h"

ESP8266WiFiMulti WiFiMulti;

void update_started()
{
  Serial.println("CALLBACK:  HTTP update process started");
}

void update_finished()
{
  Serial.println("CALLBACK:  HTTP update process finished");
}

void update_progress(int cur, int total)
{
  Serial.printf("CALLBACK:  HTTP update process at %d of %d bytes...\n", cur, total);
}

void update_error(int err)
{
  Serial.printf("CALLBACK:  HTTP update fatal error code %d\n", err);
}

FirmwareUpdateService::FirmwareUpdateService(struct FirmwareUpdateServiceParams initParams)
{
  params = initParams;
}

void FirmwareUpdateService::connect()
{
  if (!isConnected())
  {
    WiFi.mode(WIFI_STA);
    char *wifiName = new char[params.wifiName.length() + 1];
    strcpy(wifiName, params.wifiName.c_str());
    char *wifiPassword = new char[params.wifiPassword.length() + 1];
    strcpy(wifiPassword, params.wifiPassword.c_str());
    WiFiMulti.addAP(wifiName, wifiPassword);
  }
}

bool FirmwareUpdateService::isConnected()
{
  if (WiFiMulti.run() == WL_CONNECTED)
  {
    return true;
  }
  return false;
}

void FirmwareUpdateService::update(String firmwarePath)
{
  if (isConnected())
  {
    WiFiClient client;

    ESPhttpUpdate.setLedPin(LED_BUILTIN, LOW);
    ESPhttpUpdate.onStart(update_started);
    ESPhttpUpdate.onEnd(update_finished);
    ESPhttpUpdate.onProgress(update_progress);
    ESPhttpUpdate.onError(update_error);

    t_httpUpdate_return ret = ESPhttpUpdate.update(client, params.serverPath + "/" + firmwarePath);

    switch (ret)
    {
    case HTTP_UPDATE_FAILED:
      Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
      break;

    case HTTP_UPDATE_NO_UPDATES:
      Serial.println("HTTP_UPDATE_NO_UPDATES");
      break;

    case HTTP_UPDATE_OK:
      Serial.println("HTTP_UPDATE_OK");
      break;
    }
  }
}
