#include <WiFi.h>

#define led_pin   26

const char* ssid     = "VentureSky";
const char* password = "asdfghjkl";

WiFiServer server(80);

void setup()
{
    Serial.begin(115200);
    pinMode(led_pin, OUTPUT);    

    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();

}

int value = 0;

void loop()
{
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) 
  {                             
    Serial.println("New Client.");
    String currentLine = "";             
    while (client.connected()) 
    {            
      if (client.available()) 
      {             
        char c = client.read();             
        Serial.write(c);                    
        if (c == '\n') 
        {                   
          if (currentLine.length() == 0)        // End of Request
          {
            //Response Header
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            //Response Body
            client.print("<a href=\"/ON\">LED ON</a><br>");
            client.print("<a href=\"/OFF\">LED OFF</a><br>");

            // End of Response
            client.println();
            break;
          } 
          else 
          {
            currentLine = "";
          }
        } 
        else if (c != '\r') 
            currentLine += c;      
        
        if (currentLine.endsWith("GET /ON")) 
          digitalWrite(led_pin, HIGH);

        if (currentLine.endsWith("GET /OFF"))
          digitalWrite(led_pin, LOW);            
       
      }
    }

    client.stop();
    Serial.println("Client Disconnected.");
  }
}
