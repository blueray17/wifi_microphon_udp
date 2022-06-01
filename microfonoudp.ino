#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "Viruz";
const char* password = "ichalove";
int contconexion = 0;

WiFiUDP Udp;

void setup()
{
  Serial.begin(115200);
  Serial.println();

  //pinMode(5, OUTPUT);  //D1 Status LED
  //digitalWrite(15, LOW);

  WiFi.mode(WIFI_AP); //sehingga SoftAP tidak dapat dijalankan dalam mode normal
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    contconexion++;
  }
    Serial.println("WiFi connected");
    Serial.println(WiFi.localIP());
}

void loop()
{
  Udp.beginPacket("192.168.214.232", 1234);
  for (int i = 0; i < 1024; i++) {
    int old = micros();
    float analog = analogRead(17);
    analog = ((analog / 1) - 600);
//    analog = ((analog / 1) - 385);
//    Serial.println(analog);
    if (analog > 255) {
      analog = 255;
    }
    else if (analog < 0) {
      analog = 0;
    }
    Udp.write(int(analog));
    while (micros() - old < 87); // 90uSec = 1Sec/11111Hz - 3uSec untuk proses lainnya
  }
  Udp.endPacket();
  delay(5);
}
