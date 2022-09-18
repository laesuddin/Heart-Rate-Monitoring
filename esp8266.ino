#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
SoftwareSerial NodeMCU(D2,D3); //RX, TX pins

const char *ssid = "RN_902";
const char *password = "roomnumber902";

const char *host = "api.thingspeak.com";
String apiKey = "1ZK0R2WUXOHQ4Z1H";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  NodeMCU.begin(4800);
  pinMode(D2,INPUT);
  pinMode(D3,OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");

  while (WiFi.status()!= WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to ");
  Serial.println(ssid);
  Serial.println("IP adress: ");
  Serial.println(WiFi.localIP());
  

}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client;
  const int httpPort = 80;
  if(!client.connect(host, httpPort)){
    Serial.println("Connection Failed");
    delay(300);
    return;
  }
  int val = NodeMCU.parseInt();
  Serial.println(val);
  String Link="GET /update?api_key="+apiKey+"&field1=";
  Link = Link + val;
  Link = Link + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n";
  client.print(Link);
  delay(20);  
}
