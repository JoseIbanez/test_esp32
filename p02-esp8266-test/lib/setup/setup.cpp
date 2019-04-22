#include <Arduino.h>
//#include <ESP8266WiFi.h>
#include <WiFi.h>

#include "setup.h"
#include "secrets.h"
#include "config.h"

String mac;


void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  mac = WiFi.macAddress();
  Serial.print("WiFi MAC: ");
  Serial.println(mac);

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

