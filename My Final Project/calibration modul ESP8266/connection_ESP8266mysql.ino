#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
 
//Konfigurasi WiFi
WiFiClient client;
String request_string;
const char *ssid = "KOSTKU";
const char *password = "kotapendekar";
HTTPClient http;

//IP Address Server yang terpasang XAMPP
const char *host = "192.168.1.8";
 
void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
 
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }
 
  //Jika koneksi berhasil, maka akan muncul address di serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
 
int value = 0;
 
void loop() {
  // Proses Pengiriman -----------------------------------------------------------
  delay(1000);
  ++value;
 
  // Membaca Sensor Analog -------------------------------------------------------
  int datasensor1=random(0,100);            Serial.println(datasensor1);
  int sensor1=random(0,100);                Serial.println(sensor1);
  int sensor2=random(0,100);                Serial.println(sensor2);
 
  Serial.print("connecting to ");
  Serial.println(host);
  delay(1000);
 
// Mengirimkan ke alamat host dengan port 80 -----------------------------------

  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // Isi Konten yang dikirim adalah alamat ip si esp -----------------------------
  request_string = "/web-warriornux/write-data.php?data=";
  request_string += datasensor1;
  request_string += "&sensor1=";
  request_string += sensor1;
  request_string = "&sensor2=";
  request_string += sensor2;
 
  Serial.print("Requesting URL: ");
  Serial.println(request_string);
  client.print(String("GET ") + request_string + "HTTP/1.1rn" + "Host: " + host + "rn" + "Connection: closernrn");
 
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 1000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
 
// Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
 
  Serial.println();
  Serial.println("closing connection");
 }
