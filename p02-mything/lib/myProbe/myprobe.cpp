#include <Arduino.h>
#include <myprobe.h>
#include <config.h>


#define DEBUG 1





void Myprobe::set_clientId(const char* prefix, const char* mac) {

  clientId = (String)prefix + (String)mac;
  clientId.replace(":", "");
  id = clientId.c_str();

  Serial.print("ClientId: ");
  Serial.println(clientId);

  ("b/"+clientId).toCharArray(beaconTopic,sizeof(beaconTopic));
  ("q/"+clientId).toCharArray(queryTopic,sizeof(queryTopic));
  ("a/"+clientId).toCharArray(answerTopic,sizeof(answerTopic));

}




//
// readingTime function
//
int  Myprobe::readingTime(unsigned long now) {
  int ret = 0;

  // if last readomg age was 5 seconds
  if (now > lastReading && now - lastReading > TIME_READING * 1000UL) {
    lastReading = now;
    ret = 1;
  }

  return(ret);
};







//
// sleepTime function
//
int  Myprobe::sleepTime(unsigned long now){
  int ret = 0;

  // if up for 30 seconds it time to sleep
  if (now - lastBoot > TIME_SLEEP * 1000UL) {
    ret = 1;
  }

  return(ret);
};





void Myprobe::setup_gpio() {

  pinMode(SENSOR_1, OUTPUT);
  digitalWrite(SENSOR_1, HIGH);

  pinMode(SENSOR_2, OUTPUT);
  digitalWrite(SENSOR_2, HIGH);

}


