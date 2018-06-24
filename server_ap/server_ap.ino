#include <WiFi.h>

WiFiServer server(80);

#define LEDC_CHANNEL        0
#define LEDC_TIMER_RES      10
#define LEDC_PWM_FREQ       5000
#define LED_PIN             26

int max_brightness = 1023;
int brightness = 0;

const char* ssid     = "ESP-AP-Test";
const char* password = "1234567890";

void setup()
{
  Serial.begin(115200);
  ledcSetup(LEDC_CHANNEL, LEDC_PWM_FREQ, LEDC_TIMER_RES);
  ledcAttachPin(LED_PIN, LEDC_CHANNEL);

  WiFi.mode(WIFI_AP);
  WiFi.softAP();
  server.begin();
}

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
            client.print("<form action=\"/\" method=\"get\">");
            client.print("<input name=\"led\" type=\"text\">");
            client.print("<input type=\"submit\" value=\"Set\">");
            client.print("</form>");

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

        if (currentLine.endsWith("GET /?led="))
        {
          String brightness = "";
          char b = client.read();
          while (b >= '0' && b <= '9')
          {
            brightness += b;
            b = client.read();
          }
          if (brightness != "")
          {
            ledcWrite(LEDC_CHANNEL, map(brightness.toInt(), 0, 100, 0, 1023));
            Serial.print(brightness);
          }
          Serial.print(b);
        }
      }
    }

    client.stop();
    Serial.println("Client Disconnected.");
  }
}
