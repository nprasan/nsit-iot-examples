int i = 0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  if(Serial.available())
  {
    i = Serial.parseInt();
  }
  Serial.print("i = ");
  Serial.println(i);
  i++;
  delay(100);
}
