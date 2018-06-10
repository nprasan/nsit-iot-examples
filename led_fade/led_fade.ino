#define LEDC_CHANNEL        0
#define LEDC_TIMER_RES      13
#define LEDC_PWM_FREQ       5000
#define LED_PIN             26

int max_brightness = 8191;    
int fadeAmount = 100;
int brightness = 0;

void setup() {
  ledcSetup(LEDC_CHANNEL, LEDC_PWM_FREQ, LEDC_TIMER_RES);
  ledcAttachPin(LED_PIN, LEDC_CHANNEL);
}

void loop() {
  brightness = brightness + fadeAmount;
  ledcWrite(LEDC_CHANNEL, brightness);
  if (brightness <= 0 || brightness >= max_brightness) 
  {
    fadeAmount = -fadeAmount;
  }
  delay(30);
}
