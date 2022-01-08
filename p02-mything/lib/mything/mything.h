#ifndef MYTHING_H
#define MYTHING_H

#ifdef ESP32
#include "esp_system.h"
#include <ESP32Servo.h>
#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  10      /* Time ESP32 will go to sleep (in seconds) */
#endif

class Mything {



public:
    Mything() {}

    int curTime = 0;
    unsigned long lastBoot = 0;
    unsigned long lastBeacon = 0;
    unsigned long lastOrder = 0;
    String relayStatus = "0000";
    unsigned int relayList[4];
    unsigned int azimuth = 0;
    unsigned int elevation = 0;
    Servo servo_az;
    Servo servo_ev;

    #ifdef ESP32
    hw_timer_t *timer = NULL;
    #endif

    String clientId = "";

    const char*  id;
    char   beaconTopic[30];
    char   queryTopic[30];
    char   answerTopic[30];

    void parse_cmd(byte *message, unsigned int length);
    void set_clientId(const char* prefix, const char* mac);

    int  beaconTime(unsigned long now);
    int  endTime(unsigned long now);
    void watchdog(unsigned long now);

    void setup_gpio();
    void update_gpio();

    void setup_pwm();
    void update_pwm();

};

#endif
