# WiFi Parameters Example

## Description
This example demonstrates how to connect the ESP8266 to a Wi-Fi network and print various Wi-Fi parameters to the Serial Monitor, such as BSSID, RSSI, encryption type, available networks, connection status, and MAC address.

## Hardware Required
- ESP8266 microcontroller
- USB cable for programming

## Circuit Diagram
No additional components are required for this example.

## Code Explanation

Here's the full code used in this example:

```cpp
#include <ESP8266WiFi.h>

const char* ssid = "30";
const char* password = "12345678";

void setup(void) {
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s\n", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  // BSSID
  Serial.print("BSSID: ");
  Serial.println(WiFi.BSSIDstr());

  // RSSI
  Serial.print("RSSI: ");
  Serial.println(WiFi.RSSI());

  // Encryption Type
  Serial.print("Encryption Type: ");
  printEncryptionType();

  // Scan Networks
  int n = WiFi.scanNetworks();
  Serial.println("Scan Networks:");
  for (int i = 0; i < n; ++i) {
    Serial.print("  Network Name: ");
    Serial.println(WiFi.SSID(i));
    Serial.print("  Signal Strength: ");
    Serial.println(WiFi.RSSI(i));
    Serial.print("  Encryption Type: ");
    Serial.println(getEncryptionType(WiFi.encryptionType(i)));
    Serial.println();
  }

  // Status
  Serial.print("Status: ");
  Serial.println(getWiFiStatus(WiFi.status()));

  // MAC Address
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());
}

void loop() {
  delay(10000);
}

void printEncryptionType() {
  int n = WiFi.scanNetworks();
  for (int i = 0; i < n; ++i) {
    if (WiFi.SSID(i) == ssid) {
      Serial.println(getEncryptionType(WiFi.encryptionType(i)));
      return;
    }
  }
  Serial.println("Unknown");
}

String getEncryptionType(int type) {
  switch (type) {
    case ENC_TYPE_WEP:
      return "WEP";
    case ENC_TYPE_TKIP:
      return "WPA/TKIP";
    case ENC_TYPE_CCMP:
      return "WPA2/CCMP";
    case ENC_TYPE_NONE:
      return "None";
    case ENC_TYPE_AUTO:
      return "Auto";
    default:
      return "Unknown";
  }
}

String getWiFiStatus(int status) {
  switch (status) {
    case WL_IDLE_STATUS:
      return "Idle";
    case WL_NO_SSID_AVAIL:
      return "No SSID Available";
    case WL_SCAN_COMPLETED:
      return "Scan Completed";
    case WL_CONNECTED:
      return "Connected";
    case WL_CONNECT_FAILED:
      return "Connect Failed";
    case WL_CONNECTION_LOST:
      return "Connection Lost";
    case WL_DISCONNECTED:
      return "Disconnected";
    default:
      return "Unknown";
  }
}
```

## How to Run

Follow these steps to run the example code on your ESP8266:

1. **Open the `WiFiParameters.ino` file** in the Arduino IDE.
2. **Enter your Wi-Fi SSID and password** in the code.
3. **Select the correct board and port** in the Arduino IDE:
   - Go to `Tools > Board > NodeMCU 1.0 (ESP-12E Module)`
   - Go to `Tools > Port > COMx` (select the appropriate port)
4. **Upload the code** to the ESP8266.
5. **Open the Serial Monitor** in the Arduino IDE (Tools > Serial Monitor) and set the baud rate to `115200`.
6. You should see messages indicating the connection process and various Wi-Fi parameters.

## Expected Output

When the code runs successfully, the Serial Monitor will display:

```
23:28:33.782 -> Connecting to 30
23:28:34.388 -> .............
23:28:41.105 -> Connected, IP address: 192.168.38.53
23:28:41.105 -> BSSID: 76:B8:9C:20:B1:03
23:28:41.106 -> RSSI: -28
23:28:41.106 -> Encryption Type: WPA2/CCMP
23:28:44.270 -> Scan Networks:
23:28:44.270 ->   Network Name: 30
23:28:44.270 ->   Signal Strength: -23
23:28:44.270 ->   Encryption Type: WPA2/CCMP
23:28:44.270 -> 
23:28:44.270 ->   Network Name: MORARJI
23:28:44.270 ->   Signal Strength: -84
23:28:44.270 ->   Encryption Type: Auto
23:28:44.270 -> 
23:28:44.270 -> Status: Connected
23:28:44.270 -> MAC Address: 08:3A:8D:CC:ED:AD
```

### Troubleshooting

- **Incorrect SSID or Password**: Ensure the correct SSID and password are entered.
- **Connection Issues**: Check that the ESP8266 is within range of the Wi-Fi network.
- **Board and Port Settings**: Verify the correct board and port settings in the Arduino IDE.

## Additional Resources

- [ESP8266WiFi Station Class Documentation](https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/station-class.html)
- [Arduino WiFi Library Documentation](https://www.arduino.cc/reference/en/libraries/wifi/)
