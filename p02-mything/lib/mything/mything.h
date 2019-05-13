#ifndef MYTHING_H
#define MYTHING_H

#include "esp_system.h"


class Mything {



public:
    Mything() {}

    int curTime = 0;
    unsigned long lastBoot = 0;
    unsigned long lastBeacon = 0;
    unsigned long lastOrder = 0;
    String relayStatus = "0000";
    unsigned int relayList[4];

    hw_timer_t *timer = NULL;


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

};

#endif
