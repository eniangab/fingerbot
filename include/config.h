#ifndef CONFIG_H
#define CONFIG_H

// GPIO Pins
#define SOLENOID_PIN 12        // GPIO pin for solenoid control
#define SOLENOID_PULSE_MS 200  // Activation duration in milliseconds

// WiFi
#define WiFi_SSID "YOUR_SSID"           // Update with your WiFi name
#define WiFi_PASSWORD "YOUR_PASSWORD"   // Update with your WiFi password

// Web Server
#define WEB_SERVER_PORT 80

// Storage (NVS)
#define NVS_NAMESPACE "fingerbot"
#define NVS_KEY_PRESS_COUNT "press_count"
#define NVS_KEY_LAST_PRESS "last_press"

#endif