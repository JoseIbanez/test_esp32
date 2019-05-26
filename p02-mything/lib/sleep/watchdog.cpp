#include <Arduino.h>
#include "esp_system.h"
#include <watchdog.h>


#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  900      /* Time ESP32 will go to sleep (in seconds) */
hw_timer_t *timer = NULL;


//
// watchdog reset function
//
void IRAM_ATTR resetModule() {
  ets_printf("\nreboot\n");
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  esp_deep_sleep_start();
  //esp_restart();
}


//
// watchdog function
//
void watchdog() {
  timerWrite(timer, 0); //reset timer (feed watchdog)
};


//
// watchdog function
//
void setup_watchdog() {
  timer = timerBegin(0, 80, true);                  //timer 0, div 80
  timerAttachInterrupt(timer, &resetModule, true);  //attach callback
  timerAlarmWrite(timer, 5 * 1000 * 1000, false); //set time in us
  timerAlarmEnable(timer);
};
