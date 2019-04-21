#ifndef MYMQTT_H
#define MYMQTT_H

#include <PubSubClient.h>

class Mymqtt {

private:
    PubSubClient client;


public:
    Mymqtt() {}
    int setClient(PubSubClient pubsubclient);
    int add (int a, int b);
    int sub (int a, int b);
    String relayStatus = "0000";

    void parse_cmd(byte *message, unsigned int length);


    int curTime = 0;
    long lastBeacon = 0;
    long lastOrder = 0;
    //int mul (int a, int b);
    //int div (int a, int b);
};

#endif
