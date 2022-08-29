#include<Servo.h>
Servo servo;
int pos;
int ldr;
const int ledPin = 6;     // This is GPIO4 pin which is labeled as D1 on NodeMCU
const int ldrPin = A0;
int servoPin = 3;
void setup() {
  // put your setup code here, to run once:
  servo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
int ldrStatus = analogRead(ldrPin);
  if (ldrStatus <= 350){
    Serial.println(ldrStatus);//if the value goes higher and equal to 20 then Led will Glow else no
    digitalWrite(ledPin, HIGH);
    servo.write(90);
 
    delay (100);
    Serial.println("----------- SERVO ACTIVATED -----------");
  }
  else
  {
    digitalWrite(ledPin, LOW);
    servo.write(0);
    delay (100);
    Serial.println("SERVO DEACTIVATED");
  }
}