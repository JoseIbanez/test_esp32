#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "myprobe.h"
#include "config.h"
#include "setup.h"
#include "secrets.h"
#include "sleep.h"
#include "watchdog.h"

WiFiClient espClient;
PubSubClient client(espClient);
Myprobe myprobe;


//
// mqtt_reconnect function
//
int mqtt_reconnect() {

  if (client.connected()) {
    return 0;
  }
  
  Serial.print("Attempting MQTT connection...");
  // Attempt to connect
  if (!client.connect(myprobe.id)) {
    Serial.print("failed, rc=");
    Serial.print(client.state());
    Serial.println(" try again in 1 seconds");
    delay(1000);
    return -1;
  }
  Serial.println("Connected.");
  
  // Subscribe
  Serial.print("Suscribed to topic=");
  Serial.println(myprobe.queryTopic);
  client.subscribe(myprobe.queryTopic);

  return 0;
}


//
// mqtt callback function
//
void callback(char* rTopic, byte* message, unsigned int length) {
  digitalWrite(LED_BUILTIN, LOW);
  Serial.print("Message arrived on topic: ");
  Serial.println(rTopic);

  // Send answer
  client.publish(myprobe.answerTopic, "ok");

  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
}


//
// send_reading
//
void send_reading() {
    
    char topic[50];

    float moisture = 0;
    float value = 0;
    char  moisString[8];

    // get data
    moisture = analogRead(ANALOG_1);
    // Convert the value to a char array
    dtostrf(moisture, 1, 2, moisString);
    Serial.print("Moisture: ");
    Serial.println(moisString);
    // Prepare topic
    strcpy(topic,"r/");
    strcat(topic,myprobe.id);
    strcat(topic,".A0/");
    strcat(topic,MQTT_TOPIC_MOIS);
    // Send msg
    client.publish(topic, moisString);


    // get data
    moisture = analogRead(ANALOG_2);
    // Convert the value to a char array
    dtostrf(moisture, 1, 2, moisString);
    Serial.print("Moisture: ");
    Serial.println(moisString);
    // Prepare topic
    strcpy(topic,"r/");
    strcat(topic,myprobe.id);
    strcat(topic,".A1/");
    strcat(topic,MQTT_TOPIC_MOIS);
    // Send msg
    client.publish(topic, moisString);


    #ifdef ANALOG_BAT
    //
    // get battery voltage
    //
    value = analogRead(ANALOG_BAT);
    // Convert the value to a char array
    dtostrf(value, 1, 2, moisString);
    Serial.print("Battery: ");
    Serial.println(moisString);
    // Prepare topic
    strcpy(topic,"r/");
    strcat(topic,myprobe.id);
    strcat(topic,".A9/");
    strcat(topic,MQTT_TOPIC_BATT);
    // Send msg
    client.publish(topic, moisString);
    #endif


  }



//
// Arduino setup
//
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  myprobe.lastBoot = millis();
  Serial.begin(115200);
  setup_wifi();  
  setup_sleep();
  setup_watchdog();

  myprobe.setup_gpio();
  myprobe.set_clientId("ESP", WiFi.macAddress().c_str());
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);

  digitalWrite(LED_BUILTIN, HIGH);
}


//
// Arduino main loop
// 
void loop() {

  unsigned long now = millis();
  watchdog();

  if (myprobe.sleepTime(now)) {
    client.disconnect();
    sleep_now();
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi no ready");
    delay(3 * 1000);
    return;
  }

  // Check mqtt connection
  if(mqtt_reconnect() < 0) {
    Serial.println("Mqtt no ready");
    delay(3 * 1000);
    return;
  }

  client.loop();
  
  // Send beacon message or Send reading
  if (myprobe.readingTime(now) > 0) {
    send_reading();
  }

}