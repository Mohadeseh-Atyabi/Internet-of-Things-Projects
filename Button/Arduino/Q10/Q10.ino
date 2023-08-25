#include <Keypad.h>
#include <Servo.h>
#include <LiquidCrystal.h>

const String trueUsername[3] = {"11", "22", "33"};
const String truePassword[3] = {"111", "222", "333"};

const byte ROWS = 4; 
const byte COLS = 4; 

const int pirPin[3] = {22, 25, 28};
const int ledPin[3] = {23, 26, 29};

char keys[ROWS][COLS] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'C', '0', '=', '+'}
};
byte rowPins[ROWS] = {46, 47, 48, 49}; 
byte colPins[COLS] = {50, 51, 52, 53}; 

Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); 
LiquidCrystal lcd(16, 17, 18, 19, 20, 21);
Servo servo;

int parkingCapacity[3] = {1, 1, 1};
String userParked[3] = {"", "", ""};
int loginTime[3];
String enteredUser = "";
String enteredPass = "";
char state;
int passIndex;
bool userExists = false;

void printCapacity();
void welcome(int i, String enteredUser);
void resetCursor();

void setup() {
  pinMode(pirPin[0], INPUT);
  pinMode(pirPin[1], INPUT);
  pinMode(pirPin[2], INPUT);  

  pinMode(ledPin[0], OUTPUT);
  pinMode(ledPin[1], OUTPUT);
  pinMode(ledPin[2], OUTPUT);

  servo.attach(24);
  
  Serial.begin(9600);
  lcd.begin(16, 4);

  state = 'S';
  passIndex = -1;
}

void loop() {
  printCapacity();

  char key = customKeypad.getKey();
  if (key) {
    Serial.println(key);
  }

  // This is the start state where user asks to enter by pressing + key
  if (state == 'S') {
    if (key == '+'){
      state = 'A';
      lcd.clear();
      printCapacity();
      lcd.setCursor(0, 1);
      lcd.print("Enter Username"); 
    }
    else if (key == '-') {
      state = 'D';
    }
  }
  // This is the state where the user enters the username
  else if (state == 'A') {
    if (key && key != '=') {
      enteredUser += key;
    }
    else if (key && key == '=') {
      for (int i=0; i<3; i++){
        if (enteredUser == userParked[i]) {
          lcd.clear();
          printCapacity();
          lcd.setCursor(0, 1);
          lcd.write("User Exists");
          Serial.println("User exists");
          userExists = true;
          enteredUser = "";
          state = 'S';
          break;
        }
      }
      if (!userExists) {
        for (int i=0; i<3; i++) {
          if (enteredUser == trueUsername[i]) {
            Serial.println("Username was OK");
            passIndex = i;
            state = 'B';
            resetCursor();
            lcd.print("Enter Password");
            break;
          }
        }
        if (passIndex == -1) {
          Serial.println("No Username");
          resetCursor();
          lcd.print("No Username");
          state = 'S';
          enteredUser = "";
        }
        passIndex = -1;
      }
      userExists = false;
    }
  }
  // This is the state where the user enters the password
  else if (state == 'B') {
    if (key && key != '=') {
      enteredPass += key;
    }
    else if (key && key == '=') {
      if (parkingCapacity[0] == 0 && parkingCapacity[1] == 0 && parkingCapacity[2] == 0) {
        Serial.print("No Empty Space");
      }
      else {
        for (int i=0; i<3; i++) {
          if (enteredPass == truePassword[i] && enteredUser == trueUsername[i]) {
            Serial.println("Enterd Successfully");
            state = 'C';
            passIndex = i;
            loginTime[i] = millis();
            welcome(i, enteredUser);
            break;
          }
        }
        if (passIndex == -1) {
          Serial.println("Enter Failed");
          resetCursor();
          lcd.print("Enter Failed");
          state = 'S';
          enteredUser = "";
        }
        passIndex = -1;
        enteredPass = "";
      }
    }
  }
  // This is the state where the user enterd the floor and lokking for space to park
  else if (state == 'C') {
    for (int i=0; i<3; i++) {
      if (digitalRead(pirPin[i]) == HIGH && userParked[i] == "") {
        delay(1000);
        Serial.println("--------------------");
        if (digitalRead(pirPin[i]) == HIGH) {
          parkingCapacity[i] = 0;
          digitalWrite(ledPin[i], HIGH);
          userParked[i] = enteredUser;
          enteredUser = "";
          resetCursor();
          lcd.print("Park Successful");
          state = 'S';
          break;
        }
      }
    }
  }
  // This is the state that the user wants to exit the parking
  else if (state == 'D') {
     if (key && key != '=') {
      enteredUser += key;
    }
    else if (key && key == '=') {
      for (int i=0; i<3; i++){
        if (enteredUser == userParked[i]) {
          lcd.clear();
          printCapacity();
          lcd.setCursor(0, 1);
          lcd.write("User Exists");
          Serial.println("User exists");
          userExists = true;
          state = 'E';
          break;
        }
      }
      if (!userExists) {
        resetCursor();
        lcd.print("Invalid User");
        Serial.println("Invalid User");
        state = 'S';
        enteredUser = "";
      }
      userExists = false;
    }
  }
  else if (state == 'E') {
    if (key && key != '=') {
      enteredPass += key;
    }
    else if (key && key == '=') {
      for (int i=0; i<3; i++) {
        if (enteredPass == truePassword[i] && enteredUser == trueUsername[i]) {
          int price = millis() - loginTime[i];
          resetCursor();
          lcd.print("Cost:" + String(price / 60));
          loginTime[i] = "";
          passIndex = i;
        }
        if (enteredUser == userParked[i]) {
          userParked[i] = "";
          parkingCapacity[i] = 1;
          digitalWrite(ledPin[i], LOW);
          lcd.setCursor(0, 2);
          lcd.print("User Leaved");
          servo.write(180);
          delay(500);
          servo.write(90);
          state = 'S';
          Serial.println(enteredPass);
        }
      }
      if (passIndex == -1) {
          Serial.println("Wrong Password");
          resetCursor();
          lcd.print("Wrong Password");
          state = 'S';
      }
      passIndex = -1;
      enteredUser = "";
      enteredPass = "";
    }
  }
}

void printCapacity() {
  lcd.setCursor(0, 0);
  lcd.print("A0:");
  lcd.print(parkingCapacity[0]);
  lcd.print(" A1:");
  lcd.print(parkingCapacity[1]);
  lcd.print(" A2:");
  lcd.print(parkingCapacity[2]);
}

void welcome(int i, String enteredUser) {
  lcd.clear();
  printCapacity();
  lcd.setCursor(0, 1);
  lcd.write("Welcome");
  lcd.setCursor(0, 2);
  lcd.print("User:" + enteredUser);
  servo.write(180);
  delay(500);
  servo.write(90);
}

void resetCursor() {
  lcd.clear();
  printCapacity();
  lcd.setCursor(0, 1);
}
