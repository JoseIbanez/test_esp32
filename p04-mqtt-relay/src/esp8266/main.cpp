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




//
// mqtt_reconnect function
//
int mqtt_reconnect() {

  if (client.connected()) {
    return 0;
  }
  
  Serial.print("Attempting MQTT connection...");
  // Attempt to connect
  if (!client.connect(mything.id)) {
    Serial.print("failed, rc=");
    Serial.print(client.state());
    Serial.println(" try again in 1 seconds");
    delay(1000);
    return -1;
  }
  Serial.println("Connected.");
  
  // Subscribe
  Serial.print("Suscribed to topic=");
  Serial.println(mything.queryTopic);
  client.subscribe(mything.queryTopic);

  return 0;
}

//
// mqtt callback function
//
void callback(char* rTopic, byte* message, unsigned int length) {
  digitalWrite(LED_BUILTIN, LOW);
  Serial.print("Message arrived on topic: ");
  Serial.println(rTopic);

  mything.parse_cmd(message, length);
  mything.update_gpio();
  

  // Send answer
  client.publish(mything.answerTopic, "ok");

  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
}

//
// Arduino setup
//
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(9600);
  lastBoot = millis();
  setup_wifi();  

  mything.setup_gpio();
  mything.set_clientId("ESP", WiFi.macAddress().c_str());
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);

  digitalWrite(LED_BUILTIN, HIGH);
}


//
// Arduino main loop
// 
void loop() {

  long now = millis();

  if (WiFi.status() != WL_CONNECTED) {
    //Serial.println("Deepsleep mode for 30 sec.");
    //ESP.deepSleep(300 * 10000000);
    Serial.println("Restart in 10 sec.");
    delay(10 * 10000);
    ESP.restart();
  }

  // sanity, reset after 24 hours
  if (now - lastBoot > 24*3600*1000 && mything.curTime == 0) {
    ESP.restart();
  }

  // Check mqtt connection
  if(mqtt_reconnect() < 0) {
    return;
  }

  client.loop();
  
  // Send beacon message
  if (mything.beaconTime(now) > 0) {
    client.publish(mything.beaconTopic, "ok. v.0.1-20200321");
  }


  //blink LED_BUILTIN when relays are up
  if (mything.curTime > 0) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
  }


  // end of time
  if (mything.endTime(now)>0) {
    mything.update_gpio();
  }


}