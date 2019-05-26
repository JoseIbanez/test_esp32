#ifndef MYPROBE_H
#define MYPROBE_H


class Myprobe {



public:
    Myprobe() {}

    unsigned long lastBoot = 0;
    unsigned long lastReading = 0;


    String clientId = "";
    const char*  id;
    char   beaconTopic[30];
    char   queryTopic[30];
    char   answerTopic[30];


    void set_clientId(const char* prefix, const char* mac);
    void setup_gpio();

    int readingTime(unsigned long now);
    int sleepTime(unsigned long now);


};

#endif
