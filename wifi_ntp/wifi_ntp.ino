#include <WiFi.h>
#include "time.h"

const char* ssid       = "VentureSky";
const char* password   = "1234567890";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 19800;
const int   daylightOffset_sec = 0;

void printLocalTime()
{
  struct tm timestamp;
  if(!getLocalTime(&timestamp)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timestamp, "%X, %x");
}

void setup()
{
  Serial.begin(115200);
  
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");
  
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop()
{
  delay(1000);
  printLocalTime();
}
