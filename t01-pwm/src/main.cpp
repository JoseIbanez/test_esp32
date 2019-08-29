#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h> //You can download this library below

//set default address 0x40
Adafruit_PWMServoDriver servoController = Adafruit_PWMServoDriver(); 
 
const uint8_t frequency = 50;    // Frecuencia PWM de 50Hz o T=20ms
const uint16_t ServoMinTicks = 50; // ancho de pulso en ticks para pocicion 0°
const uint16_t ServoMaxTicks = 500; // ancho de pulso en ticks para la pocicion 180°
 
void setup()
{
   Serial.begin(115200);
   Serial.print("hi");
   servoController.begin();
   servoController.setPWMFreq(frequency );
}
 
void loop()
{
   for (uint16_t duty = ServoMinTicks; duty < ServoMaxTicks; duty += 8) {
      for (uint8_t n = 0; n<16; n++) {
         servoController.setPWM(n, 0, duty);
      }
      Serial.println(duty);
      delay(500);
   }
   delay(1000);
   Serial.print("+");


   for (uint16_t duty = ServoMaxTicks; duty > ServoMinTicks; duty -= 8) {
      for (uint8_t n = 0; n<16; n++) {
         servoController.setPWM(n, 0, duty);
      }
   }
   delay(1000);
   Serial.print("-");

}
