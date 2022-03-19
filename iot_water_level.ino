//Conf Blynk
#define BLYNK_TEMPLATE_ID "TMPLML2Ny5K1"
#define BLYNK_DEVICE_NAME "ESP32"
#define k 0.034

//Library
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>


char auth[] = "WObJuTK4UMhaJQO7qXFsQdUbe8GB_vI0";

char ssid[] = "TEGUH ATAS";
char pass[] = "cisitulama49";

//Ultrasonic
const int trigPin = 5;
const int echoPin = 18;
int state = 0;
//Variable and Constant` 
long duration;
float distance;

int relay =15;

BLYNK_CONNECTED() {
    Blynk.syncVirtual(V0);
}

BLYNK_WRITE(V0) {
  int pinValue = param.asInt();
  digitalWrite(relay, pinValue);
}

BLYNK_READ(V1) //Blynk app has something on V5
{
  Blynk.virtualWrite(V1, distance); //sending to Blynk
}

void setup()
{
  pinMode(relay, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Serial.begin(115200);
  delay(100);

  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
  Blynk.virtualWrite(V1, distance);
  

  //Pulses
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //Duration
  duration = pulseIn(echoPin, HIGH);
  //Distance
  distance = duration * k/2;
  distance = map(distance,30,0,0,100);
  
  if(distance < 20){
    state = 1;
  }
  if(distance>=80){
    state = 0;
  }
  if(state ==1&&distance<20){
    digitalWrite(relay, HIGH);
    Blynk.virtualWrite(V2, HIGH);
  }
  if(state == 0&&distance>80){
    digitalWrite(relay, LOW);
    Blynk.virtualWrite(V2, LOW);
  }
  
  //print
  Serial.print("ketinggian");
  Serial.println(distance);
}
