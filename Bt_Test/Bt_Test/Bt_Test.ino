
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("$$$");
  delay(100);
  Serial.println("SM,0");
  delay(100);
  Serial.println("U,115200,N");
  delay(100);
  Serial.begin(115200);
  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("T,75;P,7.2;C,2.76");
  delay(1000);
}
