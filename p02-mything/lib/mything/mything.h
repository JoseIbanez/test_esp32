#ifndef MYTHING_H
#define MYTHING_H



class Mything {



public:
    Mything() {}

    int curTime = 0;
    long lastBeacon = 0;
    long lastOrder = 0;
    String relayStatus = "0000";
    unsigned int relayList[4];


    String clientId = "";

    const char*  id;
    char   beaconTopic[30];
    char   queryTopic[30];
    char   answerTopic[30];

    void parse_cmd(byte *message, unsigned int length);
    void set_clientId(const char* prefix, const char* mac);

    int  beaconTime(long now);
    int  endTime(long now);

    void setup_gpio();
    void update_gpio();

};

#endif
