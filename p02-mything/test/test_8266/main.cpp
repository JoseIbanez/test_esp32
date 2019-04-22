#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "mything.h"
#include "config.h"
#include "setup.h"
#include "secrets.h"

WiFiClient espClient;
PubSubClient client(espClient);
Mything mything;

long lastBoot = 0;



void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(9600);
  lastBoot = millis();
  setup_wifi();  
  mything.set_clientId("ESP", "T:E:S:T");
  client.setServer(MQTT_SERVER, MQTT_PORT);
  digitalWrite(LED_BUILTIN, HIGH);
}


void loop() {

  long now = millis();

  if (WiFi.status() != WL_CONNECTED) {
    //sleep_now();
  }


  client.loop();

  mything.parse_cmd((byte*)"0010;0101",9);
  delay(10000);
}