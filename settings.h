#ifndef START_MESSAGE
#define START_MESSAGE "LOCAL BUILD RUN"
#endif

#ifndef VERSION
#define VERSION 1
#endif

#ifndef DEBUG
#define DEBUG true
#endif

#define SERIAL_BAUDRATE 74880

#define BOOT_COUNT_UPDATE 30 // SLEEP_TIME * BOOT_COUNT_UPDATE = период запроса обновлений (10 минут)

#define WIFI_NAME "tplink140"
#define WIFI_PASSWORD "12love34"

#define SERVER_PATH "http://192.168.0.129:3000"
#define API_PATH (String(SERVER_PATH) + "/api")

#ifndef SENSOR_POSITION
#define SENSOR_POSITION "cabinet"
#endif

#define TEMP_SENSOR_TYPE 0 // 0 - sht40, 1 - aht10

#define SLEEP_TIME 20e6 // 20 sec

#define TEMPERATURE_DIFF 0.2
#define HUMIDITY_DIFF 1
#define CARBON_DIOXIDE_DIFF 50

#if TEMP_SENSOR_TYPE == 0
#define tempSensor shtTempSensor
#elif TEMP_SENSOR_TYPE == 1
#define tempSensor ahtTempSensor
#endif

#if !DEBUG
#define Serial nullSerial
#endif