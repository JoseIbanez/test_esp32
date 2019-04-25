#include <Arduino.h>

#ifdef ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif

#include "setup.h"
#include "secrets.h"
#include "config.h"



void setup_wifi() {
  delay(100);
  int count = 0;
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    count++;
    if (count>60) {
      Serial.println("");
      Serial.println("WiFi setup failed");
      return;
    }
  }

  Serial.println("");
  Serial.println("WiFi connected");

	String mac = WiFi.macAddress();
  Serial.print("WiFi MAC: ");
	Serial.println(mac);

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

