#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "mything.h"
#include "config.h"
#include "setup.h"
#include "secrets.h"
#include "sleep.h"

WiFiClient espClient;
PubSubClient client(espClient);
Mything mything;
long lastBoot = 0;
long lastMsg = 0;



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

  //mything.parse_cmd(message, length);
  //update_gpio(relayStatus);

  // Send answer
  client.publish(mything.answerTopic, "ok");

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
    strcat(topic,mything.id);
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
    strcat(topic,mything.id);
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
    strcat(topic,mything.id);
    strcat(topic,".A9/");
    strcat(topic,MQTT_TOPIC_BATT);
    // Send msg
    client.publish(topic, moisString);
    #endif


    /*
    //humidity = bme.readHumidity();
    float humidity = 50;

    // Convert the value to a char array
    char humString[8];
    dtostrf(humidity, 1, 2, humString);
    Serial.print("Humidity: ");
    Serial.println(humString);
    strcpy(topic,"r/");
    strcat(topic,clientId);
    strcat(topic,"/");
    strcat(topic,MQTT_TOPIC_HUMI);
    client.publish(topic, humString);
    */
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
  setup_sleep();

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

  if (now - lastBoot > 30000 || WiFi.status() != WL_CONNECTED) {
    client.disconnect();
    sleep_now();
  }

  // Check mqtt connection
  if(mqtt_reconnect() < 0) {
    return;
  }

  client.loop();
  
  // Send beacon message
  //if (mything.beaconTime(now) > 0) {
  //  client.publish(mything.beaconTopic, "ok");
  //}

  // Send reading
  if (now - lastMsg > 5000) {
    lastMsg = now;
    send_reading();
  }


}