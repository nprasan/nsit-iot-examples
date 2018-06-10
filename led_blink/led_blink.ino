void setup() {
  // put your setup code here, to run once:
  pinMode(26, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(26, LOW);
  delay(1000);
  digitalWrite(26, HIGH);
  delay(1000);
}
