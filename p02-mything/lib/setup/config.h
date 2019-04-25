#ifndef H_CONFIG
#define H_CONFIG


// Add your MQTT Broker IP address, example:
//const char* mqtt_server = "192.168.1.144";
//const char* mqtt_server = "YOUR_MQTT_BROKER_IP_ADDRESS";
#define MQTT_SERVER      "192.168.1.19"
#define MQTT_PORT        1883
#define MQTT_CLIENT_ID   "ESP"
#define MQTT_TOPIC_OUT   "output"
#define MQTT_TOPIC_TEMP  "temp"
#define MQTT_TOPIC_HUMI  "humi"
#define MQTT_TOPIC_MOIS  "mois"
#define MQTT_TOPIC_BATT  "batt"
#define MQTT_TOPIC_CALLHOME  "callhome"


#ifdef ARDUINO_LOLIN_D32
#define ANALOG_1 34
#define ANALOG_2 32
#define ANALOG_BAT 35
#endif

#ifdef ARDUINO_ESP32_DEV
#define ANALOG_1 A0
#define ANALOG_2 A3
#endif


#endif