#include <WiFi.h>
#include "DHT.h"

#define DHTPIN 14     // what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

const char* ssid     = "Venture Sky";
const char* password = "qwertyuiop";

const char* host = "api.thingspeak.com";
WiFiClient client;
const int httpPort = 80;

void setup() 
{
    Serial.begin(115200);
    Serial.println();

    dht.begin();
    
    Serial.println("Initializing DHT11");
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    Serial.print("connecting to ");
    Serial.println(host);  // put your setup code here, to run once:

}

void loop() 
{
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) 
    {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
  
    String url = "/update?api_key=7E2QWXYONZL5AA3L&field1=";
    url = url + t;
    url = url + "&field2=";
    url = url + h;

    Serial.print("Requesting URL: ");
    Serial.println(url);

    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }
    
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");

    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }

    bool headerComplete = false;
    while(client.available()) {
        String line = client.readStringUntil('\r');
        if(headerComplete)
        {
          int dataCount = line.toInt();
          if(dataCount)
            Serial.println("Data Uploaded");
          else
            Serial.println("Upload Failed");
        }
        if(line == "\n")
          headerComplete = true;

    }

    delay(20000);
}
