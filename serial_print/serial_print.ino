int i;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  i = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("i = ");
  Serial.println(i);
  i++;
  delay(1000);
}
