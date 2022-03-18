//Conf Blynk
#define BLYNK_TEMPLATE_ID "xxxxx"
#define BLYNK_DEVICE_NAME "xxxxx"

//Library
#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial
#define APP_DEBUG
#define USE_ESP32C3_DEV_MODULE
#include "BlynkEdgent.h"

//Ultrasonic
const int trigPin = 5;
const int echoPin = 18;
//Variable and Constant
#define k 0.034
long duration;
float distance;


BLYNK_WRITE(V0) {
  int pinValue = param.asInt();
  digitalWrite(0,pinValue);
}

BLYNK_READ(V1) //Blynk app has something on V5
{
  sensorData = distance; //reading the sensor on A0
  Blynk.virtualWrite(V1, sensorData); //sending to Blynk
}

void setup()
{
  pinMode(0, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Serial.begin(115200);
  delay(100);

  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();

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
