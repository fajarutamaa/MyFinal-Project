#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS 5000

PulseOximeter pox;
uint32_t tsLastReport = 0;

void onBeatDetected() {
  Serial.println("Beat!");
}

void setup() {
  Serial.begin(115200);
  Serial.print("Initializing pulse oximeter..");
  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");
  }
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
  pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop() {
  getBPM();
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
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    Serial.print("Heart rate: ");
    Serial.print(Average_HR);
    Serial.println(" bpm");
    tsLastReport = millis();
  }
}
  
