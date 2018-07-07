int threshold = 40;
bool touchDetected = false;

void gotTouch(){
 touchDetected = true;
}

void setup() {
  Serial.begin(115200);
  touchAttachInterrupt(T0, gotTouch, threshold);
}

void loop(){
  if(touchDetected){
    touchDetected = false;
    Serial.println("Touch Detected");
    delay(100);
  }
}
