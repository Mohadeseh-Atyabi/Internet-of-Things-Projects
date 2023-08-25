const int ledPin = 53;
const int ldrPin = A0;
bool turnOn = false;
bool near = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int ldrState = analogRead(ldrPin);
  Serial.println(ldrState);

  if (ldrState >= 950 && !near && !turnOn) {
    near = true; //It means that the light must be turned on
  }
  else if (ldrState >= 950 && !near && turnOn) {
    digitalWrite(ledPin, LOW);
    turnOn = false;
    delay(1000);
  }
  else if (ldrState < 90 && near && !turnOn) {
    digitalWrite(ledPin, HIGH);
    near = false;
    turnOn = true;
  }
}
