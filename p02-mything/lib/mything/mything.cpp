#include <Arduino.h>
#include <mything.h>
#include <config.h>

#define DEBUG 1


// Parse cmd
void Mything::parse_cmd(byte *message, unsigned int length) {

  String command;

  Serial.print("Message: ");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    command += (char)message[i];
  }
  Serial.println();


  #ifdef DEBUG
  Serial.print("Command: ");
  Serial.println(command);
  #endif

  //Asking for status ?
  if ((command == "STATUS") || (command == "S")) {
    Serial.print("curTime: ");
    Serial.println(String(curTime));
    Serial.print("relayStatus: ");
    Serial.println(relayStatus);
    return;
  }
  
  int pos = command.indexOf(';');
  if (pos<0) {
    return;
  }

  curTime     =  command.substring(1,pos).toInt();
  relayStatus =  command.substring(pos+1);
  lastOrder   =  millis();

  #ifdef DEBUG
  Serial.print("curTime: ");
  Serial.println(String(curTime));
  Serial.print("relayStatus: ");
  Serial.println(relayStatus);
  #endif

  // Sanity
  if (curTime <= 0) {
    Serial.println("curTime: 0");
    curTime = 0;
    relayStatus = "0000";
  }

  return;
}




void Mything::set_clientId(const char* prefix, const char* mac) {

  clientId = (String)prefix + (String)mac;
  //clientId.concat(mac);
  clientId.replace(":", "");
  id = clientId.c_str();

  Serial.print("ClientId: ");
  Serial.println(clientId);

  ("b/"+clientId).toCharArray(beaconTopic,sizeof(beaconTopic));
  ("q/"+clientId).toCharArray(queryTopic,sizeof(queryTopic));
  ("a/"+clientId).toCharArray(answerTopic,sizeof(answerTopic));

}








//
// beaconTime function
//
int  Mything::beaconTime(long int now) {
  int ret = 0;

  // if last beach age was 1 minute
  if (now - lastBeacon > 60000) {
    lastBeacon = now;
    ret = 1;
  }

  return(ret);
};

//
// endTime function
//
int  Mything::endTime(long int now){
  int ret = 0;

  // if "on" and last order older than curTime
  if ( curTime > 0   &&   (now - lastOrder) > curTime*1000 ) {
    Serial.println("curTime: 0");
    curTime = 0;
    relayStatus = "0000";
    ret = 1;
  }

  return(ret);
};




//
// setup_gpio
//
void Mything::setup_gpio() {
  
  relayList[0] = RELAY1;
  relayList[1] = RELAY2;
  relayList[2] = RELAY3;
  relayList[3] = RELAY4;

  int length = (sizeof(relayList)/sizeof(*relayList));

  for (int i=0; i < length; i++) {
    pinMode(relayList[i], OUTPUT);
    digitalWrite(relayList[i],HIGH);
  }

}


//
// update_gpio
//
void Mything::update_gpio() {

  int pinValue = HIGH;
  int length = (sizeof(relayList)/sizeof(*relayList));

  Serial.print("Relays set to: ");
  //Serial.println(status);

  for (int i=0; i < length; i++){

    if (relayStatus.charAt(i) == '1') {
      Serial.print("1");
      pinValue = LOW;
    } else {
      Serial.print("0");
      pinValue = HIGH;
    }

    digitalWrite(relayList[i],pinValue);
  }

  Serial.println(".");
}










