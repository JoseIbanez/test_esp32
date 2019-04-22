#ifndef MYTHING_H
#define MYTHING_H



class Mything {



public:
    Mything() {}

    int curTime = 0;
    long lastBeacon = 0;
    long lastOrder = 0;
    String relayStatus = "0000";
    String clientId = "";

    void parse_cmd(byte *message, unsigned int length);
    void set_clientId(char* prefix, char* mac);
    int  check_timeout(long int);

};

#endif
