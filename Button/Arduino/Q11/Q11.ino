#include <Servo.h>

const int buzzerPin = 7;
const int servoPin = 6;
const int gasPin = 5;
const int flamePin = 2;

bool gasHigh = false;
Servo servo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(servoPin);
  pinMode(flamePin, INPUT);
  pinMode(gasPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int gas = digitalRead(gasPin);
  int flame = digitalRead(flamePin);
  Serial.print("Gas: ");
  Serial.print(gas);
  Serial.print("    Flame: ");
  Serial.println(flame);
  
  if (flame == HIGH) {
    tone(buzzerPin, 1000);
    servo.write(180);
    delay(1000);
    noTone(buzzerPin);
    servo.write(90);
  }
  if (gas == HIGH && !gasHigh) {
    tone(buzzerPin, 1000);
    servo.write(180);
    gasHigh = true;
  }
  else if (gas == LOW && gasHigh) {
    noTone(buzzerPin);
    servo.write(90);
    gasHigh = false;
  }
}
