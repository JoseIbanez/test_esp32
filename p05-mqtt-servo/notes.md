TOPIC="q/ESP3C71BF6ACDB8"

/usr/bin/mosquitto_pub -t $TOPIC -m "SET AZ;20"
/usr/bin/mosquitto_pub -t $TOPIC -m "SET EV;20"
sleep 1
/usr/bin/mosquitto_pub -t $TOPIC -m "SET AZ;120"
/usr/bin/mosquitto_pub -t $TOPIC -m "SET EV;0"
sleep 1
/usr/bin/mosquitto_pub -t $TOPIC -m "SET AZ;0"
/usr/bin/mosquitto_pub -t $TOPIC -m "SET EV;120"
sleep 1
/usr/bin/mosquitto_pub -t $TOPIC -m "SET AZ;120"
/usr/bin/mosquitto_pub -t $TOPIC -m "SET EV;0"
sleep 1
/usr/bin/mosquitto_pub -t $TOPIC -m "SET AZ;0"
/usr/bin/mosquitto_pub -t $TOPIC -m "SET EV;120"
