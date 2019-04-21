#include <mything.h>





// Parse cmd
void Mything::parse_cmd(byte *message, unsigned int length) {


  Serial.print(". Message: ");
  String messageOrder;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageOrder += (char)message[i];
  }
  Serial.println();



  char delimiter[] = ";";
  char* ptr;
  char buf[15];

  #ifdef DEBUG
  Serial.println(input);
  #endif

  //Asking for status ?
  if ((input == "STATUS") || (input == "S")) {
    return 0;
  }
  
  input.toCharArray(buf, sizeof(buf));

  // Get TimeOut
  ptr = strtok(buf, delimiter);
  if (ptr != NULL) {
    curTime = String(ptr).toInt();
    lastOrder = millis();
    Serial.println("Uptime: " + String(curTime));
  }

  // Get Gpio Status
  ptr = strtok (NULL, delimiter);
  if (ptr != NULL) {
    relayStatus = String(ptr);
    Serial.println("Relay status: " + relayStatus);
  }

  // Sanity
  if (curTime <= 0) {
    curTime = 0;
    relayStatus = "0000";
  }

  return(0);
}




void Mything::set_clientId(char* mac) {

  strcpy(clientId,MQTT_CLIENT_ID);
  //Serial.print("Client MAC: ");
  //Serial.println(mac);
  int length = mac.length();
  int pos = strlen(clientId);

  for (int i = 0; i < length ; i++) {

    if ((char)mac[i] == ':') {
      continue;
    }

    if (pos > clientSize-2) {
      break;
    }

    clientId[pos] = (char)mac[i];
    pos++;
  }  

  clientId[pos]=0;
  Serial.print("ClientId: ");
  Serial.print(clientId);
  Serial.println(".");
}




int Mything::check_timeout(long now) {


}
