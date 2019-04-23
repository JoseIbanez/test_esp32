#include <Arduino.h>
#include <mything.h>

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
    return;
  }
  
  int pos = command.indexOf(';');
  if (pos<0) {
    return;
  }

  curTime     =  command.substring(1,pos).toInt();
  relayStatus =  command.substring(pos+1);

  #ifdef DEBUG
  Serial.print("curTime: ");
  Serial.println(String(curTime));
  Serial.print("relayStatus: ");
  Serial.println(relayStatus);
  #endif

  // Sanity
  if (curTime <= 0) {
    curTime = 0;
    relayStatus = "0000";
  }

  return;
}




void Mything::set_clientId(const char* prefix, const char* mac) {

  clientId = String(prefix);
  clientId.concat(mac);
  clientId.replace(":", "");

  Serial.print("ClientId: ");
  Serial.print(clientId);
  Serial.println(".");
}




int Mything::check_timeout(long now) {
  return 0;
}
