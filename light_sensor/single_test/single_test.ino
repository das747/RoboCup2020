void setup() {
  Serial.begin(9600);

}

void loop() {
  Serial.println(float(map(analogRead(A0), 0, 1024, 0, 500)) / 100);
  delay(10);
}
