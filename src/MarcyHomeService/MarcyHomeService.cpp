#include "MarcyHomeService.h"

double round2(double value)
{
  return (int)(value * 100 + 0.5) / 100.0;
}

MarcyHomeService::MarcyHomeService(struct MarcyHomeServiceParams initParams)
{
  params = initParams;
}

void MarcyHomeService::connect()
{
  Serial.println("WiFi connect");
  if (!isConnected())
  {
    WiFi.begin(params.wifiName, params.wifiPassword);
  }
}

bool MarcyHomeService::isConnected()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("WiFi connected! IP address: ");
    Serial.println(getIp());
    return true;
  }
  return false;
}

String MarcyHomeService::getIp()
{
  return WiFi.localIP().toString().c_str();
}

void MarcyHomeService::setSensorData(SensorData data)
{
  if (isConnected())
  {

    WiFiClient client;
    HTTPClient http;

    Serial.print("[HTTP] begin...\n");

    http.begin(client, params.apiPath + "/sensor");
    http.addHeader("Content-Type", "application/json");

    Serial.print("[HTTP] POST...\n");

    JsonDocument doc;
    doc["version"] = params.version;
    doc["position"] = params.position;
    doc["temperature"] = round2(data.temperature);
    doc["humidity"] = round2(data.humidity);
    doc["carbon_dioxide"] = data.carbonDioxide;
    String body;
    serializeJson(doc, body);

    Serial.println("Send body:");
    Serial.println(body);

    int httpCode = http.POST(body);

    if (httpCode > 0)
    {
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);
    }
    else
    {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }
}

String MarcyHomeService::getNewFirmware()
{
  if (isConnected())
  {

    WiFiClient client;
    HTTPClient http;

    Serial.print("[HTTP] begin...\n");

    String path = params.apiPath + "/firmware?version=" + String(params.version) + "&key=" + params.position;

    http.begin(client, path);
    http.addHeader("Content-Type", "application/octet-stream");

    Serial.println("Send request:");
    Serial.println(path);

    int httpCode = http.GET();

    if (httpCode > 0)
    {
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);
      if (httpCode == HTTP_CODE_OK)
      {
        JsonDocument doc;
        const String &payload = http.getString();
        deserializeJson(doc, payload);
        return doc["path"];
      }
    }
    else
    {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }
  return "";
}
