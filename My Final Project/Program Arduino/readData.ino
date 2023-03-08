//Library Sensor
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <KRtcs3200.h>

//MQ 135
#define RL 10                           //nilai RL =10 pada sensor
#define m -0.417                        //hasil perhitungan gradient
#define b 0.858                         //hasil perhitungan perpotongan
#define Ro 10                           //hasil pengukuran RO
#define MQ_sensor A0                    //definisi variabel

const int numReadings = 5;              //nilai pengambilan sample pembacaan sebesar 5 kali
float readings[numReadings];
int readIndex = 0;
float total = 0;
float average = 0;

//TCS3200
KRtcs3200 sensor(4, 5, 6, 7, 8);        //pin configure S0, S1, S2, S3, Out

//MAX30100
PulseOximeter pox;

void setup() {
  Serial.begin(9600);
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
  pox.setOnBeatDetectedCallback(onBeatDetected);
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop() {
  getColor();
  getAmmonia();
  getBPM();
  Serial.println(String(grayscale));
  Serial.print("A");
  delay(1000);
  Serial.print("B");
  Serial.print(String(average));
  delay(1000);
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    Serial.print(String(Average_HR));
    Serial.print("C");
    delay(1000);
  }
}

void getColor() {
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
  grayscale = ((red_value + green_value + blue_value) / 3);
}

void getAmmonia() {
  float VRL;
  float RS;
  float ratio;

  VRL = analogRead(MQ_sensor) * (5 / 1023.0);           //konversi analog ke tegangan
  RS = (5.0 / VRL - 1) * 10 ;                           //rumus untuk RS
  ratio = RS / Ro;                                      //rumus mencari ratio
  float ppm = pow(10, ((log10(ratio) - b) / m));        //rumus mencari ppm

  total = total - readings[readIndex];
  readings[readIndex] = ppm;
  total = total + readings[readIndex];
  readIndex = readIndex + 1;
  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  average = total / numReadings;
}

void getBPM() {
  float t, BPM;
  int Average_HR = 0;
  int MeasurementsToAverage = 5;
  for (int i = 0; i < MeasurementsToAverage; i++) {
    pox.update();
    BPM = round(pox.getHeartRate() * 0.75);
    Average_HR += BPM;
  }
  Average_HR /= MeasurementsToAverage;
}
