char c;
String dataIn;
int8_t indexOfA, indexOfB, indexOfC;
String data1, data2, data3;

void setup() {
  Serial.begin(9600);
}

void loop() {
  while (Serial.available() > 0) {
    c = Serial.read();
    if (c == '\n') {
      break;
    } else {
      dataIn += c;
    }
  }
  if (c == '\n') {
    parse();
    Serial.println("Data 1 = "+data1);
    Serial.println("Data 2 = "+data2);
    Serial.println("Data 3 = "+data3);
    Serial.println("========================");
    c = 0;
    dataIn = "";
  }
}

void parse() {
  indexOfA = dataIn.indexOf("A");
  indexOfB = dataIn.indexOf("B");
  indexOfC = dataIn.indexOf("C");

  data1 = dataIn.substring(0, indexOfA);
  data2 = dataIn.substring(indexOfA + 1, indexOfB);
  data3 = dataIn.substring(indexOfB + 1, indexOfC);
}
