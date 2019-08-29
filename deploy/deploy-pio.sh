#!/bin/bash

#Setup VM OS (USB support)
sudo apt-get -y update
sudo apt-get -y install python-pip linux-image-extra-virtual


# pio install 
pip install -U platformio

#udev rules
curl -fsSL https://raw.githubusercontent.com/platformio/platformio-core/develop/scripts/99-platformio-udev.rules | sudo tee /etc/udev/rules.d/99-platformio-udev.rules

platformio update
platformio lib update
