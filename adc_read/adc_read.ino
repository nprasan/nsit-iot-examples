void setup() {
  Serial.begin(115200);
}

void loop() {
  int sensorValue = analogRead(34);
  //int percent = map(sensorValue, 0, 4095, 0, 100);
  Serial.println(sensorValue);
  delay(2);
}
