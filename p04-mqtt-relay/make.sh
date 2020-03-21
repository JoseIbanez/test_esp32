#!/bin/bash

#ENV=Geekworm
#ENV=lolin32
#ENV=lolin_d32
ENV=d1mini
ENV=d1minipro

ls -l /dev/ttyUSB*
sudo chown vagrant /dev/ttyUSB0
platformio run -e $ENV -t upload -t monitor
