void setup()
{
  Serial.begin(115200);
}

void loop()
{
  Serial.println(touchRead(T0));  // get value using T0
  delay(500);
}
