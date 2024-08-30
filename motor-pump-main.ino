#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "AdafruitIO_WiFi.h"

// Wi-Fi settings
#define WIFI_SSID "<your_wifi_ssid>"
#define WIFI_PASS "<your_wifi_password>"

// Adafruit IO settings
#define AIO_USERNAME "<your_adafruit_username>"
#define AIO_KEY "<your_adafruit_key>"

// Define pins for relays
#define RELAY1_PIN D1 // GPIO 5
#define RELAY2_PIN D2 // GPIO 4

AdafruitIO_WiFi io(AIO_USERNAME, AIO_KEY, WIFI_SSID, WIFI_PASS);

// Adafruit IO Feed for motor control
AdafruitIO_Feed *motorControl = io.feed("motor-pump-control");

void setup() {
  // Initialize relay pins
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);

  // Set both relays to OFF initially
  digitalWrite(RELAY1_PIN, HIGH); // Set relay 1 to off
  digitalWrite(RELAY2_PIN, HIGH); // Set relay 2 to off
  
  // Start serial communication
  Serial.begin(115200);
  
  // Connect to Adafruit IO
  io.connect();
  
  // Wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("Connected to Adafruit IO!");

  // Setup message handler for motor control
  motorControl->onMessage(handleMessage);
}

void loop() {
  io.run(); // Keep Adafruit IO connection alive
}

// Handle incoming messages
void handleMessage(AdafruitIO_Data *data) {
  if (data->toInt() == 3) {
    Serial.println("Received relay 1 ON");
    digitalWrite(RELAY1_PIN, LOW); // activate relay 1 on receiving 3
  } else if (data->toInt() == 1) {
    Serial.println("Received relay 1 OFF");
    delay(1000);
    digitalWrite(RELAY1_PIN, HIGH); // deactivate relay 1 on receiving 1
    // (This is green button release action)
  } else if (data->toInt() == 4) {
    Serial.println("Received relay 2 ON");
    digitalWrite(RELAY2_PIN, LOW); // activate relay 2 on receiving 4
  } else if (data->toInt() == 2) {
    Serial.println("Received relay 2 OFF");
    delay(1000);
    digitalWrite(RELAY2_PIN, HIGH); // deactivate relay 2 on receiving 2
    // (This is green button release action)
  }
}