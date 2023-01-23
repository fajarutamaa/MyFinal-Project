#include <KRtcs3200.h>

KRtcs3200 sensor(4, 5, 6, 7, 8);  //pin configure S0, S1, S2, S3, Out

void setup() {
  Serial.begin(9600);
  sensor.begin();
}

void loop() {
  int red_value = 0;
  int green_value = 0;
  int blue_value = 0;
  int grayscale = 0;

  red_value = sensor.getRed();
  delay(200);
  green_value = sensor.getGreen();
  delay(200);
  blue_value = sensor.getBlue();
  delay(200);
  grayscale = (red_value + green_value + blue_value) / 3;

  Serial.print("Red value = ");
  Serial.print(red_value);
  Serial.print("  Green value = ");
  Serial.print(green_value);
  Serial.print("  Blue value = ");
  Serial.println(blue_value);
  Serial.println(grayscale);
  delay(1000);


  if (grayscale <= 125) {
    Serial.println("Dehidrasi");
  }
  else if ((125 < grayscale) && (grayscale<=150)) {
    Serial.println("Dehidrasi Ringan"); 
  }
  else if (grayscale > 150){
    Serial.println("Normal");
  }
}
