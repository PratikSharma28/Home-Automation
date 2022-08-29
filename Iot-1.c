#define BLYNK_TEMPLATE_ID "TMPLmkPK2zLb"
#define BLYNK_DEVICE_NAME "Automation Project"
#include <Servo.h>
#define BLYNK_PRINT Serial
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS D2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
 
char auth[] = "9rHE4kAtm4JpDskjarXP99146_YcnEKJ";               //Authentication code sent by Blynk
char ssid[] = "TP_LINK";                        //WiFi SSID
char pass[] = "parth1892";


int value1 = 5;
int value2 = 12;
int value3 = 14;
int value4 = 16;


int relay_pin1 = 14; // D5
int relay_pin2 = 13;//D7
int relay_pin3 = 15;//D8
int relay_pin4 = 12;//D6

Servo servo;

BLYNK_WRITE(V8) {
servo.write(param.asInt());
}



#define DHTPIN 2          // Digital pin 4

#define DHTTYPE DHT11     // DHT 11
DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;

const int sensor_pin = A0;  /* Connect Soil moisture analog sensor pin to A0 of NodeMCU */
int soilPin_relay = D0;


void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);  //V5 is for Humidity
  Blynk.virtualWrite(V6, t);  //V6 is for Temperature
}

void setup() 
{
  Serial.begin(115200);
 

  Blynk.begin(auth, ssid, pass);
  delay(1000);
  dht.begin();
  pinMode(relay_pin1,OUTPUT);
  digitalWrite(relay_pin1,HIGH);
  pinMode(relay_pin2,OUTPUT);
  digitalWrite(relay_pin2,HIGH);
  pinMode(relay_pin3,OUTPUT);
  digitalWrite(relay_pin3,HIGH);
  pinMode(relay_pin4,OUTPUT);
  digitalWrite(relay_pin4,HIGH);
  servo.attach(0); // 0 means D3 pin of ESP8266 
  timer.setInterval(1000L, sendSensor);

 
  
   pinMode(soilPin_relay, OUTPUT);
  
}

void loop()
{
   
  
   //moisture sensor
   float moisture_percentage;

  moisture_percentage = ( 100.00 - ( (analogRead(sensor_pin)/1023.00) * 100.00 ) );

  Serial.print("Soil Moisture(in Percentage) = ");
  Serial.print(moisture_percentage);
  Serial.println("%");
if (moisture_percentage >= 40)
{
   digitalWrite(soilPin_relay, HIGH);
}else {
    // turn LED off:
    digitalWrite(soilPin_relay, LOW);
  }
   Blynk.virtualWrite(V7,moisture_percentage);  //V5 is for Humidity
     
 delay(500);
 timer.run(); // Initiates SimpleTimer
  
  Blynk.run();
 
}
//  Blynk.virtualWrite(V4,value0);

  BLYNK_WRITE(V0) { //Button Widget is writing to pin V0
  int pinValue1 = param.asInt();
  digitalWrite(relay_pin1, pinValue1);
  Blynk.virtualWrite(V4,value1);
  delay(100);
}
BLYNK_WRITE(V1) { //Button Widget is writing to pin V0
  int pinValue2 = param.asInt();
  digitalWrite(relay_pin2, pinValue2);
  Blynk.virtualWrite(V4,value2);
  delay(100);
}

BLYNK_WRITE(V2) { //Button Widget is writing to pin V0
  int pinValue3 = param.asInt();
  digitalWrite(relay_pin3, pinValue3);
  Blynk.virtualWrite(V4,value3);
  delay(100);
}
BLYNK_WRITE(V3) { //Button Widget is writing to pin V0
  int pinValue4 = param.asInt();
  digitalWrite(relay_pin4, pinValue4);
  Blynk.virtualWrite(V4,value4);
  delay(100);
}