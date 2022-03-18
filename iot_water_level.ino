//Conf Blynk
#define BLYNK_TEMPLATE_ID "xxxxxx"
#define BLYNK_DEVICE_NAME "xxxxx"

//Library
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "xxxxx";

char ssid[] = "xxxx";
char pass[] = "xxxx";

//Ultrasonic
const int trigPin = 5;
const int echoPin = 18;
//Variable and Constant
#define k 0.034
long duration;
float distance;


BLYNK_WRITE(V0) {
  int pinValue = param.asInt();
  digitalWrite(15, pinValue);
}

BLYNK_READ(V1) //Blynk app has something on V5
{
  Blynk.virtualWrite(V1, random(200)); //sending to Blynk
}

void setup()
{
  pinMode(15, OUTPUT);
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
  //distance = duration * k/2;

  //random for demo
  distance = random(200);
  
  //print
  Serial.print("ketinggian");
  Serial.println(distance);
}
