#include <ESP8266WiFi.h>

//Konfigurasi WiFi
const char *ssid = "KOSTKU";
const char *password = "kotapendekar";

//IP Address Server yang terpasang XAMPP
const char *host = "192.168.1.8";

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
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
  int datasensor1 = random(0, 100);
  Serial.println(datasensor1);

  int sensor1 = random(0, 100);
  Serial.println(sensor1);

  int sensor2 = random(0, 100);
  Serial.println(sensor2);

  Serial.print("connecting to ");
  Serial.println(host);
  delay(1000);

  // Mengirimkan ke alamat host dengan port 80 -----------------------------------
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // // Isi Konten yang dikirim adalah alamat ip si esp -----------------------------
  String url = "/web-warriornux/write-data.php?data=";
  url += datasensor1;
  delay(1000);

  String url1 = "&sensor1=";
  url1 += sensor1;
  delay(1000);

  String url2 = "&sensor2=";
  url2 += sensor2;
  delay(1000);

  Serial.print("Requesting URL: ");
  Serial.println(url);

  // Mengirimkan Request ke Server -----------------------------------------------
  client.print(String("GET ") + url + url1 + url2 + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
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
