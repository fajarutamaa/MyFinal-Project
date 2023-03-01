void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("01");
  Serial.print("A");
  Serial.print("02");
  Serial.print("B");
  Serial.print("03");
  Serial.print("C");
  Serial.print("\n");
  delay(1000);
}
