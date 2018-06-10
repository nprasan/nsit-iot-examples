#include "WiFi.h"

void setup()
{
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
}

void loop()
{
    Serial.println("New Scan Starting ...");
    int n = WiFi.scanNetworks();
    if (n == 0) {
        Serial.println("no networks found");
    } else {
        for (int i = 0; i < n; ++i) {
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" ==> ");
            Serial.print(WiFi.RSSI(i));
            Serial.println(" dB");
        }
    }
    delay(5000);
}
