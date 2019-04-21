#Platformio basics

## Install boards
platformio platform install atmelavr
platformio platform install espressif32

## Install libs
platformio lib install 

#Project init
platformio init --board esp32dev 
platformio lib list

#Compile and load
platformio run -t upload -t monitor



