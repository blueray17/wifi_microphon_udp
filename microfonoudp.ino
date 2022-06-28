#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "****";
const char* password = "****";
int contconexion = 0;
WiFiUDP Udp;
char char_ip[67];

void setup()
{
  Serial.begin(115200);
  Serial.println();
  String IPAdd;
  int StringCount = 0;
  String strs[4];
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  WiFi.mode(WIFI_STA); //sehingga SoftAP tidak dapat dijalankan dalam mode normal
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    contconexion++;
  }
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
  IPAdd = WiFi.localIP().toString();
  while (IPAdd.length() > 0) {
    int index = IPAdd.indexOf('.');
    if (index == -1){
      strs[StringCount++] = IPAdd;
      break;
    }else{
      strs[StringCount++] = IPAdd.substring(0, index);
      IPAdd = IPAdd.substring(index + 1);
    }
  }
  String iip = strs[0]+"."+strs[1]+"."+strs[2]+"."+"232";
  int str_len = iip.length() + 1; 
  char char_array[str_len];
  iip.toCharArray(char_array, str_len);
  strcpy(char_ip,char_array);
  Serial.print("ip adalah :");Serial.println(char_ip);
}

void loop()
{  
  Udp.beginPacket(char_ip, 1234);
  for (int i = 0; i < 1024; i++) {
    int old = micros();
    float analog = analogRead(17);
    analog = (analog/1024)*255;
    Udp.write(int(analog));
    //while (micros() - old < 90); // 90uSec = 1Sec/11111Hz - 3uSec untuk proses lainnya
  }
  Udp.endPacket();
  delay(4);
}
