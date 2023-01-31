#include <WiFiManager.h>
#include <strings_en.h>

void setup() {
  // put your setup code here, to run once:
  WiFi.mode(WIFI_STA);
  Serial.begin(9600);
  WiFiManager wm;
  bool res;
  res = wm.autoConnect("AutoconnectAP", "password");
  if (!res) {
    Serial.println("Mohon maaf gagal terhubung");
  } else {
    Serial.println("Yeay, terhubung :)");
  }
  Serial.print("Terhubung dengan IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:
}
