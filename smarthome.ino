#include <Servo.h>
Servo myservo;
#define PIR_PIN 2
#define  BUZZER_PIN 5
#define RELAY_PIN1 8
#define RELAY_PIN2 6
#define GAS_PIN A3
#define trigger_PIN 4
#define ECHO_PIN 3
#define PHOTO_PIN A0

unsigned long lasttime=millis();
unsigned long timedelay=100;

void triggersensor(){
  digitalWrite(trigger_PIN,LOW);
  delay(2);
  digitalWrite(trigger_PIN,HIGH);
  delay(10);
  digitalWrite(trigger_PIN,LOW);
  
}
 double getdistance(){
  double durationMicros=pulseIn(ECHO_PIN,HIGH);
  double distance=durationMicros/58.0;
  return distance;
}


void setup(){
  Serial.begin(115200);
  pinMode(PIR_PIN,INPUT);
  pinMode(BUZZER_PIN,OUTPUT);
  pinMode(RELAY_PIN1,OUTPUT);
  pinMode(RELAY_PIN2,OUTPUT);
  pinMode(trigger_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);
  myservo.attach(7);
}
void loop(){
 int value=analogRead(GAS_PIN);
  if(value>=250){
    tone(BUZZER_PIN,450);
    triggersensor();
   int disp= getdistance();
    if(disp<15){
      myservo.write(disp);
    }
    else{
      myservo.write(LOW);
    }
    int pir=digitalRead(PIR_PIN);
    if(pir==HIGH){
      digitalWrite(RELAY_PIN1,HIGH);
    }
    else{
      digitalWrite(RELAY_PIN1,LOW);
    }
    int photo=analogRead(PHOTO_PIN);
    if(photo<400){
      digitalWrite(RELAY_PIN2,HIGH);
    }
    else{
      digitalWrite(RELAY_PIN2,LOW);
    }
  }
  else{
    noTone(BUZZER_PIN);
  }
}
