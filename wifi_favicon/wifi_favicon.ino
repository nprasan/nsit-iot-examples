#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiClient.h>
#include "icon.h"

const char* ssid = "LocalAreaNetwork";
const char* password = "yeahright";

WiFiServer server(80);

void setup(void)
{  
    Serial.begin(115200);

    WiFi.begin(ssid, password);
    Serial.println("");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    if (!MDNS.begin("esp32")) {
        Serial.println("Error setting up MDNS responder!");
        while(1) {
            delay(1000);
        }
    }
    Serial.println("mDNS responder started");

    server.begin();
    Serial.println("TCP server started");

    MDNS.addService("http", "tcp", 80);
}

void loop(void)
{
    WiFiClient client = server.available();
    if (!client) {
        return;
    }
    Serial.println("");
    Serial.println("New client");

    while(client.connected() && !client.available()){
        delay(1);
    }

    String req = client.readStringUntil('\r');

    int addr_start = req.indexOf(' ');
    int addr_end = req.indexOf(' ', addr_start + 1);
    if (addr_start == -1 || addr_end == -1) {
        Serial.print("Invalid request: ");
        Serial.println(req);
        return;
    }
    req = req.substring(addr_start + 1, addr_end);
    Serial.print("Request: ");
    Serial.println(req);
    client.flush();

    String s;
    if (req == "/")
    {
        IPAddress ip = WiFi.localIP();
        String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
        s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>Hello from ESP32 at ";
        s += ipStr;
        s += "</html>\r\n\r\n";
        Serial.println("Sending 200");
        client.print(s);
    }
    else if (req == "/favicon.ico")
    {
        char resp[] = "HTTP/1.1 200 OK\r\nContent-Type: image/x-icon\r\n\r\n";
        client.print(resp);
        //client.write_P(favicon, sizeof(favicon));
        client.write(favicon, sizeof(favicon));
        client.print("\r\n\r\n");
    }
    else
    {
        s = "HTTP/1.1 404 Not Found\r\n\r\n";
        Serial.println("Sending 404");
        client.print(s);
    }
    Serial.println("Done with client");
}

