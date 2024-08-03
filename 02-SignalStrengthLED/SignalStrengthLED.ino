#include <ESP8266WiFi.h>

const char* ssid = "30";
const char* password = "12345678";
int led = LED_BUILTIN; // Use the built-in LED, usually mapped to GPIO2 (D4)

void setup() {
  pinMode(led, OUTPUT);  // Declare the built-in LED pin as an output

  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s\n", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, \nIP address: ");
  Serial.println(WiFi.localIP());

  // BSSID
  Serial.print("BSSID: ");
  Serial.println(WiFi.BSSIDstr());

  // RSSI
  Serial.print("RSSI: ");
  Serial.println(WiFi.RSSI());

  // MAC Address
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());
}

void loop() {
  int rssi = WiFi.RSSI();  // Read the RSSI value
  Serial.print("RSSI: ");
  Serial.println(rssi);

  int brightness;

  // Calculate brightness based on RSSI
  brightness = -rssi;

  Serial.print("(- RSSI): ");
  Serial.println(brightness);

  // Scale brightness to fit 0-255 range
  brightness = brightness * 255;
  brightness = brightness / 70;

  Serial.print("Brightness LED_value: ");
  Serial.println(brightness);

  // Cap brightness to a maximum of 255
  if (brightness >= 255) {
    brightness = 255;
    Serial.print("Brightness capped: ");
    Serial.println(brightness);
  }

  // Set LED brightness
  analogWrite(led, brightness);

  delay(300); // Delay to avoid rapid changes
}
