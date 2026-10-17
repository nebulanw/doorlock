// include the library code:
#include <LiquidCrystal.h>
#include <Wire.h>
//byte sReceive = 0;
char x = ' ';
boolean noLoop = false;
int sStatus = 0;

// initialize the library with the numbers of the interface pins
//LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
//Serial.begin(9600);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(9600);
  //Serial.begin(9600);
  // Print a message to the LCD.
  //lcd.print("Scan RFID Card");
  Wire.begin(9);
  Wire.onReceive(receiveEvent);
}

void receiveEvent() {
  //Serial.println("Transmission");
  while (Wire.available() > 0) {
    x = Wire.read();
    if (x == '1') {
      sStatus = 1;
      noLoop = false;
    }
    else if (x == '2') {
      sStatus = 2;
      noLoop = false;
    }
    else if (x == '3') {
      sStatus = 3;
      noLoop = false;
    }
    else if (x == '4') {
      sStatus = 4;
      noLoop = false;
    }
    else if (x == '5') {
      sStatus = 5;
      noLoop = false;
    }
    else if (x == '6') {
      sStatus = 6;
      noLoop = false;
    }
    //noLoop = false;
    //Serial.println(x);
  }
}

void loop() {
  //Serial.println(sStatus);
  if (sStatus == 1 && noLoop == false) {
    lcd.clear();
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Swipe RFID Card");
    noLoop = true;
  }
  if (sStatus == 2 && noLoop == false) {
    lcd.clear();
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("**Door  Locked**");
    lcd.setCursor(0, 1);
    lcd.print("****RFID OFF****");
    noLoop = true;
  }
  if (sStatus == 3 && noLoop == false) {
    lcd.clear();
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("*Door  Unlocked*");
    lcd.setCursor(0, 1);
    lcd.print("****RFID OFF****");
    noLoop = true;
  }
  if (sStatus == 4 && noLoop == false) {
    lcd.clear();
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Card 1");
    lcd.setCursor(0, 1);
    lcd.print("Door Unlocked");
    noLoop = true;
  }
  if (sStatus == 5 && noLoop == false) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Unknown Card");
    lcd.setCursor(0, 1);
    lcd.print("Try Again");
    noLoop = true;
  }
  if (sStatus == 6 && noLoop == false) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Card 2");
    lcd.setCursor(0, 1);
    lcd.print("Door Unlocked");
    noLoop = true;
  }
  //setup();
}
