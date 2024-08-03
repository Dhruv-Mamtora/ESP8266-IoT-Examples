# Signal Strength LED Example

## Description
This example demonstrates how to connect an ESP8266 to a Wi-Fi network and adjust the brightness of the built-in LED based on the signal strength (RSSI) from the Wi-Fi network. The LED's brightness varies according to the RSSI value:

- **RSSI = -1**: Full signal strength, LED at full brightness.
- **RSSI <= -70**: Weak signal strength, LED at low brightness.
- **RSSI between -1 and -70**: LED brightness adjusts proportionally to the RSSI value.

## Hardware Required
- ESP8266 microcontroller
- USB cable for programming

## Circuit Diagram
No additional components are required for this example. The built-in LED is used for visual feedback.

## Code Explanation

Here’s the code used in this example:

```cpp
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
```

## How to Run

Follow these steps to run the example code on your ESP8266:

1. **Open the `SignalStrengthLED.ino` file** in the Arduino IDE.
2. **Enter your Wi-Fi SSID and password** in the code.
3. **Select the correct board and port** in the Arduino IDE:
   - Go to `Tools > Board > NodeMCU 1.0 (ESP-12E Module)`
   - Go to `Tools > Port > COMx` (select the appropriate port)
4. **Upload the code** to the ESP8266.
5. **Open the Serial Monitor** in the Arduino IDE (Tools > Serial Monitor) and set the baud rate to `115200`.
6. Observe the built-in LED’s brightness adjusting based on the RSSI value of the Wi-Fi signal.

## Expected Output

When the code runs successfully, the Serial Monitor will display:
```
00:05:56.015 -> .....
00:06:22.666 -> Connected, 
00:06:22.666 -> IP address: 192.168.38.53
00:06:22.666 -> BSSID: 76:B8:9C:20:B1:03
00:06:22.666 -> RSSI: -24
00:06:22.666 -> MAC Address: 08:3A:8D:CC:ED:AD
00:06:22.666 -> RSSI: -24
00:06:22.666 -> (- RSSI): 24
00:06:22.666 -> Brightness LED_value: 87
00:06:22.962 -> RSSI: -23
00:06:22.962 -> (- RSSI): 23
00:06:22.962 -> Brightness LED_value: 83
00:06:23.260 -> RSSI: -23
00:06:23.260 -> (- RSSI): 23
00:06:23.260 -> Brightness LED_value: 83
```


## Troubleshooting

- **LED Not Lighting Up**: Ensure the LED pin configuration is correct and `LED_BUILTIN` is properly defined.
- **Inconsistent Brightness**: Verify the RSSI values and ensure the brightness calculation is correct.
- **Connection Issues**: Check that the ESP8266 is within range of the Wi-Fi network and that the SSID and password are accurate.

## Additional Resources

- [ESP8266WiFi Library Documentation](https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html)
- [Arduino LED Functions](https://www.arduino.cc/reference/en/libraries/)
