#include <WiFi.h>

#define LED_PIN   26

const char* ssid     = "VentureSky";
const char* password = "asdfghjkl";

const char* host = "api.thingspeak.com";
WiFiClient client;
const int httpPort = 80;

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    
    Serial.begin(115200);
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
    Serial.println(host);

}

void loop()
{
    String url = "/talkbacks/26912/commands/execute.json?api_key=O45N7IR7RSS2D5JW";
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
    int count;
    while(client.available()) {
        String line = client.readStringUntil('\r');
        if(headerComplete)
        {
            if(++count == 2)
            {
              int n1 = line.indexOf("command_string");
              int n2 = line.indexOf(",", n1+17);
              String cmd =  line.substring(n1+17, n2-1);
              if(cmd != "")
                Serial.println(cmd);
              if(cmd == "ON")
                digitalWrite(LED_PIN, HIGH);
              if(cmd == "OFF")
                digitalWrite(LED_PIN, LOW);
                
            }
            
        }
        if(line == "\n")
        {
          headerComplete = true;
          count = 0;
        }

    }
   delay(1000);
}

