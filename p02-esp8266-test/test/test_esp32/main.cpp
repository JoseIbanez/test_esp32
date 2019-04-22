#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <gtest/gtest.h>
#include "mything.h"
#include "config.h"
#include "secrets.h"

WiFiClient espClient;
PubSubClient client(espClient);
Mything mything;

long lastBoot = 0;


namespace {
    class Mything : public ::testing::Test {
        protected:
    };


    TEST_F(Mything, clientId01) {
        mything.set_clientId("ESP", "1:2:3:4");
        EXPECT_EQ(mything.clientId, "ESP1234");
    }

    TEST_F(Mything, clientId02) {
        mything.set_clientId("ESP", "14:22:32:42:33:33");
        ASSERT_EQ(mything.clientId, "ESP142232423333");
    }

    ////////////////////////

    TEST_F(Mything, command01) {
        mything.parse_cmd((byte*)"0010;0101",9);
        ASSERT_EQ(mything.curTime, 10);
        ASSERT_EQ(mything.relayStatus, "0101");
    }

    TEST_F(Mything, command02) {
        mything.parse_cmd((byte*)"0110;0101",9);
        ASSERT_EQ(mything.curTime, 110);
        ASSERT_EQ(mything.relayStatus, "0101");
    }

    ////////////////////////

    TEST_F(Mything, command03) {
        mything.parse_cmd((byte*)"0110;0101",9);
        mything.parse_cmd((byte*)"0110",4);
        ASSERT_EQ(mything.curTime, 110);
        ASSERT_EQ(mything.relayStatus, "0101");
    }

    ////////////////////////

    TEST_F(Mything, status01) {
        mything.parse_cmd((byte*)"0110;0101",9);
        mything.parse_cmd((byte*)"S",1);
        ASSERT_EQ(mything.curTime, 110);
        ASSERT_EQ(mything.relayStatus, "0101");
    }

    TEST_F(Mything, status02) {
        mything.parse_cmd((byte*)"0110;0101",9);
        mything.parse_cmd((byte*)"STATUS",6);
        ASSERT_EQ(mything.curTime, 110);
        ASSERT_EQ(mything.relayStatus, "0101");
    }

}  // namespace





void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(9600);
  lastBoot = millis();
  testing::InitGoogleTest();
  digitalWrite(LED_BUILTIN, HIGH);
}


void loop() {

  long now = millis();

  mything.parse_cmd((byte*)"0010;0101",9);
  RUN_ALL_TESTS();
  delay(60000);
}