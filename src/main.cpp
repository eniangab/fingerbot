#include <Arduino.h>
#include <WiFi.h>
#include <Preferences.h>
#include "config.h"
#include "solenoid.h"
#include "wifi_setup.h"

// TODO: Global variables for web server, press history

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n[SETUP] Fingerbot initializing...");
  
  // Initialize GPIO
  solenoid_init();
  
  // Initialize WiFi
  wifi_init();
  wifi_connect();
  
  Serial.println("[SETUP] Fingerbot ready!");
}

void loop() {
  // TODO: Web server request handling
  // TODO: Check for press requests
  
  delay(100);
}