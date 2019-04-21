#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "config.h"
#include "setup.h"
#include "secrets.h"

WiFiClient espClient;
PubSubClient client(espClient);
Mymqtt mymqtt();

long lastBoot = 0;


char msg[50];
int value = 0;
char clientId[20];




// callback function
void callback(char* topic, byte* message, unsigned int length) {
  digitalWrite(LED_BUILTIN, LOW);
  Serial.print("Message arrived on topic: ");
  Serial.println(topic);

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
  //if (String(topic) == MQTT_TOPIC_OUT) {
  parse_cmd(messageOrder);
  //update_gpio(relayStatus);
  //}

  char aTopic[50];    
  strcpy(aTopic,"a/");
  strcat(aTopic,clientId);
  client.publish(aTopic, "ok");

  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
}


////////
int reconnect() {
  char topic[50];

  if (client.connected()) {
    // Already connected
    return 0;
  }

  Serial.print("Attempting MQTT connection...");
  // Attempt to connect
  if (!client.connect(clientId)) {
    Serial.print("failed, rc=");
    Serial.print(client.state());
    Serial.println(" try again in 1 seconds");
    delay(1000);
    return -1;
  }
  Serial.println("Connected.");
  
  // Subscribe
  strcpy(topic,"q/");
  strcat(topic,clientId);
  client.subscribe(topic);
  Serial.print("Suscribed to topic=");
  Serial.println(topic);

  return 0;
}



void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(9600);
  lastBoot = millis();
  setup_wifi();  
  set_clientId(clientId,sizeof(clientId));
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);
  digitalWrite(LED_BUILTIN, HIGH);
}


void loop() {

  long now = millis();

  if (WiFi.status() != WL_CONNECTED) {
    //sleep_now();
  }

  if(reconnect() < 0) {
      return; 
  }

  client.loop();

  // Send beacon message
  if (now - lastBeacon > 60000) {
    lastBeacon = now;
    char topic[50];    
    strcpy(topic,"b/");
    strcat(topic,clientId);
    client.publish(topic, "ok");
  }

  //blink LED_BUILTIN when relays are up
  if (curTime > 0) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
  }

  // end of time
  if ( curTime > 0   &&   (now - lastOrder) > curTime*1000 ) {
    curTime = 0;
    relayStatus = "0000";
    //update_gpio(relayStatus);
  }

}