#define RL 10                 //nilai RL =10 pada sensor
#define m -0.417              //hasil perhitungan gradient
#define b 0.858               //hasil perhitungan perpotongan
#define Ro 10                 //hasil pengukuran RO
#define MQ_sensor A0          //definisi variabel

const int numReadings = 5;    //nilai penambilan sample pembacaan sebesar 5 kali
float readings[numReadings];
int readIndex = 0;
float total = 0;
float average = 0;

void setup() {
  Serial.begin(9600);
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop() {
  float VRL;
  float RS;
  float ratio;

  VRL = analogRead(MQ_sensor) * (5 / 1023.0);       //konversi analog ke tegangan
  RS = (5.0 / VRL - 1) * 10 ;                       //rumus untuk RS
  ratio = RS / Ro;                                  //rumus mencari ratio
  float ppm = pow(10, ((log10(ratio) - b) / m));    //rumus mencari ppm

  total = total - readings[readIndex];
  readings[readIndex] = ppm;
  total = total + readings[readIndex];
  readIndex = readIndex + 1;
  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  average = total / numReadings;
  Serial.print("NH3 : ");
  Serial.print(average);
  Serial.println(" PPM");

  delay(1000);

}
