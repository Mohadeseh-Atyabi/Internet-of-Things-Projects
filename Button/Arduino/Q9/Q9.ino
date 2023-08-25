#include <Servo.h>
#include "HX711.h"

const int DOUT_PIN = 2;
const int SCK_PIN = 3;
const int buzzerPin = 6;
const int servoPin = 5;
const int greenLED = 21;
const int redLED = 20;
bool full = true;

HX711 scale;
Servo servo;

void setup() {
  Serial.begin(57600);
  scale.begin(DOUT_PIN, SCK_PIN);
  scale.set_scale(36.059);
  servo.attach(servoPin);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  delay(1000);
}

void loop() {
  int food = scale.get_units()/1000;
  Serial.print("Weigh of food: ");
  Serial.println(food);
  
  if (food >= 3) {
    if (full){
      digitalWrite(greenLED, HIGH);
      servo.write(180);
      delay(2000);
      digitalWrite(greenLED, LOW);
      servo.write(90);
    } 
    else{
      digitalWrite(redLED, LOW);
      noTone(buzzerPin);
      full = true;
    }
    delay(3000);
  }
  else {
    digitalWrite(redLED, HIGH);
    tone(buzzerPin, 1000);
    full = false;
  }
}
