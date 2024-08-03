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
