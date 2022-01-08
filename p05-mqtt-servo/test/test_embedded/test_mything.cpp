/*
 Copyright (c) 2014-present PlatformIO <contact@platformio.org>

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
**/

#include <Arduino.h>
#include <unity.h>
#include "mything.h"
#include "config.h"
#include "setup.h"
#include "secrets.h"

#include "test_servo.h"


// void setUp(void) {
// // set stuff up here
// }

// void tearDown(void) {
// // clean stuff up here
// }

void test_function_calculator_addition(void) {
    TEST_ASSERT_EQUAL(32, (25 + 7));
}

void test_cmd_status(void) {


    byte message[50];
    unsigned int l_message=0;
    Mything mything;
    const char * msg1 = "STATUS";
    int curTime;

    strcpy((char *)message,msg1);
    l_message=strlen(msg1);

    mything.parse_cmd(message, l_message);
    curTime = mything.curTime;
    TEST_ASSERT_EQUAL(curTime,0);
}




void test_cmd_relay(void) {

    byte message[50];
    unsigned int l_message=0;
    Mything mything;
    const char * msg1 = "0100;1010";
    int curTime;

    strcpy((char *)message,msg1);
    l_message=strlen(msg1);

    mything.parse_cmd(message, l_message);
    curTime = mything.curTime;
    TEST_ASSERT_EQUAL(curTime,100);
}



void test_cmd_set(void) {

    byte message[50];
    unsigned int l_message=0;
    Mything mything;
    const char * msg1 = "SET AZ;1200";
    const char * msg2 = "SET EV;900";
    int azimuth;
    int elevation;

    strcpy((char *)message,msg1);
    l_message=strlen(msg1);
    mything.parse_cmd(message, l_message);

    strcpy((char *)message,msg2);
    l_message=strlen(msg2);
    mything.parse_cmd(message, l_message);

    azimuth = mything.azimuth;
    elevation = mything.elevation;
    TEST_ASSERT_EQUAL(azimuth,1200);
    TEST_ASSERT_EQUAL(elevation,900);


}


void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();
    RUN_TEST(test_function_calculator_addition);
    RUN_TEST(test_cmd_status);
    RUN_TEST(test_cmd_relay);
    RUN_TEST(test_cmd_set);

    RUN_TEST(test_setup_pwm);
    RUN_TEST(test_update_pwm);

    UNITY_END();
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}
