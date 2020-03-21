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

#define TIME_READING 3
#define TIME_BEACON 60
#define TIME_SLEEP 15


#ifdef ARDUINO_LOLIN_D32
#define ANALOG_1 32
#define ANALOG_2 34
#define ANALOG_BAT 35
#define SENSOR_1 2
#define SENSOR_2 4
#endif

#ifdef ARDUINO_LOLIN32
#define ANALOG_1 A0
#define ANALOG_2 A3
#define RELAY1 25
#define RELAY2 26
#define RELAY3 27
#define RELAY4 14
#endif


#ifdef ARDUINO_ESP32_DEV
#define ANALOG_1 A0
#define ANALOG_2 A3
#define RELAY1 25
#define RELAY2 26
#define RELAY3 27
#define RELAY4 14
#define SENSOR_1 2
#define SENSOR_2 4
#endif


//relay ports
#ifdef ARDUINO_D1MINIPRO
#define RELAY1 16
#define RELAY2 14
#define RELAY3 12
#define RELAY4 13
#endif

//relay ports
#ifdef ARDUINO_D1MINI
#define RELAY1 16
#define RELAY2 14
#define RELAY3 12
#define RELAY4 13
#endif



//relay ports
#ifdef ARDUINO_ESP01_1M
#define RELAY1 0
#define RELAY2 0
#define RELAY3 0
#define RELAY4 0
#endif

//default replay ports
#ifndef RELAY1
#define RELAY1 2
#define RELAY2 2
#define RELAY3 2
#define RELAY4 2
#endif




#endif