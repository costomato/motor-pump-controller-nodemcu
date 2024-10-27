#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "AdafruitIO_WiFi.h"
#include <Espalexa.h>

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
Espalexa espalexa;

// Adafruit IO Feed for motor control
AdafruitIO_Feed *motorControl = io.feed("motor-pump-control");
boolean wifiConnected = false;

// Alexa callbacks
void motorControlCallback(uint8_t brightness);
boolean connectWifi();

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


  // Initialise wifi connection
  wifiConnected = connectWifi();

  if (wifiConnected)
  {
    Serial.println(":: Adding devices and starting alexa ::");
    // Initialize Espalexa devices
    espalexa.addDevice("Motor", motorControlCallback);

    // Begin Espalexa
    espalexa.begin();
    Serial.println(":: Devices added and alexa ready! ::");
  }
  else
  {
    while (1)
    {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }
}

void loop() {
  io.run(); // Keep Adafruit IO connection alive
  espalexa.loop(); // Handle Alexa commands
}

// Handle incoming messages
void handleMessage(AdafruitIO_Data *data) {
  if (data->toInt() == 3) {
    Serial.println("Received relay 1 ON. Motor start button");
    digitalWrite(RELAY1_PIN, LOW); // activate relay 1 on receiving 3
  } else if (data->toInt() == 1) {
    Serial.println("Received relay 1 OFF. Motor start button");
    delay(1000);
    digitalWrite(RELAY1_PIN, HIGH); // deactivate relay 1 on receiving 1
    // (This is green button release action)
  } else if (data->toInt() == 4) {
    Serial.println("Received relay 2 ON. Motor stop button");
    digitalWrite(RELAY2_PIN, LOW); // activate relay 2 on receiving 4
  } else if (data->toInt() == 2) {
    Serial.println("Received relay 2 OFF. Motor stop button");
    delay(1000);
    digitalWrite(RELAY2_PIN, HIGH); // deactivate relay 2 on receiving 2
    // (This is green button release action)
  }
}

void motorControlCallback(uint8_t brightness) {
  if (brightness > 0) {
    Serial.println("Alexa: Activating and deactivating relay 1 (Start)");
    digitalWrite(RELAY1_PIN, LOW); // Turn on relay 1
    delay(1000);
    digitalWrite(RELAY1_PIN, HIGH); // deactivate relay 1
    // Remember, we turn on and off the relay,
    // because it is required to only momentarily turn on and off.
    // Imitating a push button here.
  } else {
    Serial.println("Alexa: Activating and deactivating relay 2 (stop)");
    digitalWrite(RELAY2_PIN, LOW); // Turn on relay 2
    delay(1000);
    digitalWrite(RELAY2_PIN, HIGH); // Turn off relay 2
  }
}

// connect to wifi – returns true if successful or false if not
boolean connectWifi()
{
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20) {
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state) {
    Serial.print("Connected to ");
    Serial.println(WIFI_SSID);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}
