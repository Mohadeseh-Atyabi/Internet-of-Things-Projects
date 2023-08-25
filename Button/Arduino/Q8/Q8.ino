#include <Servo.h>
Servo servo1;
int servoPin = 4;
int resPin = A3; // sensor pin used
int ldrPin = A0;
String state = "close";

void serial_print(String water, String LDR);

void setup() { 
  // set up the LCD's number of columns and rows: 
  Serial.begin(9600);
  servo1.attach(servoPin);
  pinMode(resPin, INPUT);
  pinMode(ldrPin, INPUT);
} 
  
void loop() { 
  int resval = analogRead(resPin); 
  int ldr = analogRead(ldrPin);

  if (resval <= 100) { serial_print("Empty", ldr); }
  else if (resval>100 && resval<=300) { serial_print("Low", ldr); }
  else if (resval>300 && resval<=500) { serial_print("Medium", ldr); }
  else if (resval>500) { serial_print("High", ldr); }

  if (resval>300 || ldr>900) {
    if (state == "close") {
      servo1.write(180);
      state = "open";
    }
  } else if (state == "open") {
    servo1.write(90);
    state = "close";
  }
  
  delay(100); 
}

void serial_print(String water, int LDR) {
  Serial.print("Water: ");
  Serial.print(water);
  Serial.print("    LDR: ");
  Serial.println(LDR);
}
