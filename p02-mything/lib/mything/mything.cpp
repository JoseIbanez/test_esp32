#include <Arduino.h>
#include <mything.h>
#include <config.h>

#ifdef ESP32
#include "esp_system.h"
//#include "sleep.h"
#endif

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
  
  // parameter commands
  int pos = command.indexOf(';');
  if (pos<0) {
    return;
  }

  // set values
  if (command.startsWith("SET AZ;")) {
    azimuth = command.substring(pos+1).toInt();
    Serial.print("Azimuth: ");
    Serial.println(String(azimuth));
    return;
  }

  if (command.startsWith("SET EV;")) {
    elevation = command.substring(pos+1).toInt();
    Serial.print("Elevation: ");
    Serial.println(String(elevation));
    return;
  }


  //Default command set relay's values and timeout
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
int  Mything::beaconTime(unsigned long now) {
  int ret = 0;

  // if last beach age was 1 minute
  if (now - lastBeacon > 60* 1000UL) {
    lastBeacon = now;
    ret = 1;
  }

  return(ret);
};


#ifdef ESP32
//
// watchdog reset function
// 
void IRAM_ATTR resetModule() {
  ets_printf("\nreboot\n");
  
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  esp_deep_sleep_start();

  //esp_restart();
}
#endif

//
// watchdog function
//
void  Mything::watchdog(unsigned long now) {
  int ret = 0;

  #ifdef ESP32
  timerWrite(timer, 0); //reset timer (feed watchdog)
  #endif

  if (now < lastBeacon) {
    return;
  }

  // if no beacon x 3 times
  if (now - lastBeacon > 3 * 60000UL) {
    Serial.println("beaconTime failed");
    ret = 1;
  }


  // sanity, reset after 24 hours
  if (now - lastBoot > 24*3600*1000UL && curTime == 0) {
    Serial.println("daily restart");
    ret = 1;
  }


  if (ret > 0) {
    Serial.println("restarting");
    ESP.restart();
  }


};



//
// endTime function
//
int  Mything::endTime(unsigned long now){
  int ret = 0;


  // if "on" and last order older than curTime
  if ( curTime > 0   &&  now > lastOrder   &&  (now - lastOrder) > curTime * 1000UL ) {
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
  
  #ifdef ESP32
  timer = timerBegin(0, 80, true);                  //timer 0, div 80
  timerAttachInterrupt(timer, &resetModule, true);  //attach callback
  timerAlarmWrite(timer, 5 * 1000 * 1000, false); //set time in us
  timerAlarmEnable(timer);  
  #endif


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


//
// Setup pwm
//
void Mything::setup_pwm() {

	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);

	servo_az.setPeriodHertz(50);    // standard 50 hz servo
	servo_az.attach(PWM_1, 500, 2400); // attaches the servo on pin 18 to the servo object

	servo_ev.setPeriodHertz(50);    // standard 50 hz servo
	servo_ev.attach(PWM_2, 500, 2400); // attaches the servo on pin 18 to the servo object

}


void Mything::update_pwm() {
		servo_az.write(azimuth);
		servo_ev.write(elevation);
}




