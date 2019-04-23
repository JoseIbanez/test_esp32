#include <Arduino.h>
#include <WiFi.h>
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
  mything.set_clientId("ESP", WiFi.macAddress().c_str());
  client.setServer(MQTT_SERVER, MQTT_PORT);
  digitalWrite(LED_BUILTIN, HIGH);
}


////////
int mqtt_reconnect() {

  if (client.connected()) {
    return 0;
  }
  
  char topic[50];


  Serial.print("Attempting MQTT connection...");
  // Attempt to connect
  if (!client.connect(mything.clientId.c_str())) {
    Serial.print("failed, rc=");
    Serial.print(client.state());
    Serial.println(" try again in 1 seconds");
    delay(1000);
    return -1;
  }
  Serial.println("Connected.");
  
  // Subscribe
  strcpy(topic,"q/");
  strcat(topic,mything.clientId.c_str());
  client.subscribe(topic);
  Serial.print("Suscribed to topic=");
  Serial.println(topic);

  return 0;
}



void loop() {

  long now = millis();

  if (WiFi.status() != WL_CONNECTED) {
    //sleep_now();
    return;
  }

  if(mqtt_reconnect() < 0) {
      return;
  }

  client.loop();
  

  delay(5000);
}