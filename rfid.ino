// 8/10/2019 2:23PM
/* 
 *  Copyright (c) 2020
 *  Last revised 10:11PM 8-9-2021
 *  Last code revision: 2020
 */
/* Notes:
 *  Serial monitor unable to accept multiple charcters at once, fix passcode. 11:50AM 8/27/2019
 *  Support for I2C via Raspberry Pi to be added soon. Create new arduino sketch for program. Resume development. 12:32 PM 7/28/2020
 *  
 */
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <Stepper.h>
#include <Wire.h>
#define RST_PIN 49
#define SS_PIN 53
MFRC522 mfrc522(SS_PIN, RST_PIN);   
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
boolean rfidOn = true;
boolean noRefresh = false;
boolean noSerial = false;
boolean pinCorrect = false;
boolean noPythonSerial = false;
int SerialAvailable = 0;
int piezoPin = 8;
int m = 0;
int lock = 0;
int unlock = 0;
char myPin = '0';
int sysStatus = 1;
int prevStatus = 2;
int normal = 0;
char sLock = '2';
char sUnlock = '3';
char sNormal = '1';
char sOpen = '4';
char sIncorrect = '5';
int sRestore = 6;
char sSmall = '6';
char x = ' ';
boolean noMessage = false;
const int stepsPerRevolution = 530;
Stepper myStepper(stepsPerRevolution, 22, 24, 23, 25);
 
void setup() 
{
  Wire.begin(1);
  Serial.begin(9600);
  SPI.begin();     
  mfrc522.PCD_Init();
  myStepper.setSpeed(20);
  lcd.begin(16, 2);   
  String content= "";
  byte letter;
  Wire.beginTransmission(9);
  Wire.write(sNormal);
  Wire.endTransmission();
  Wire.onReceive(receiveEvent);
  //Serial.println(sysStatus);
/*  Serial.print(mfrc522.uid.size);
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
    lcd.setCursor(0, 1);
     lcd.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     lcd.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     Serial.print("Initial");
  }
  */
}
void receiveEvent() {
  while (Wire.available() > 0) {
    x = Wire.read();
    if (x == 'n' && sysStatus != 1) {
      if (sysStatus == 2) {
        prevStatus = 2;
      }
      if (sysStatus == 3) {
        prevStatus = 3;
      }
      sysStatus = 1;
      
    }
  }
}
void loop() 
{

  char passOne = '4';
  char passTwo = '8';
  char passThree = '7';
  char passFour = '5';
  char myInput = ' ';
  
  


 /* if (Serial.available()) {
    myInput = Serial.read();
    //Serial.println(myInput);
    
    /* if (myInput == 'o') {
      myStepper.step(stepsPerRevolution);
      Serial.println("open");
      tone(piezoPin, 1000, 500);
      tone(piezoPin, 100, 500);
      
    }
    if (myInput == 'c') {
      //Serial.println("Ricky");
      myStepper.step(-stepsPerRevolution);
      Serial.println("close");
      tone(piezoPin, 1000, 500);
      tone(piezoPin, 100, 500);
    }*/
//    } 
// loop();
    
    //myInput = "";
  //Exit
  SerialAvailable = Serial.available();
  if (SerialAvailable > 0) {
        //Serial.println(SerialAvailable);
    myInput = Serial.read();
    Serial.end();
    Serial.begin(9600);
    if (myInput == 'e' && sysStatus == 1) {
      myStepper.step(stepsPerRevolution);
      delay(10000);
      myStepper.step(-stepsPerRevolution);
      //SerialAvailable = false;
      return;
    }
    if (myInput == 'l' && sysStatus != 2) {
      lock = 1;
      pinCorrect = false;
      Serial.println("Please enter four-digit passcode to lock system.");
      //Serial.println("Enter first digit of passcode.");
      SerialAvailable = 0;
      return;
    }
    if (myInput == 'n' && sysStatus != 1) {
      pinCorrect = false;
      Serial.println("Please enter four-digit passcode to resume normal system operation.");
      //Serial.println("Enter first digit of passcode.");
      normal = 1;
      //SerialAvailable = 0;
      return;
    }
    if (myInput == 'u' && sysStatus != 3) {
      pinCorrect = false;
      unlock = 1;
      Serial.println("Please enter four-digit passcode to unlock system.");
      //Serial.println("Enter first digit of passcode.");
      //SerialAvailable = false;
      return;
    }
    if (myInput == 'r') {
      Serial.println(sysStatus);
    }
  } 

  //Lock mode
  if (lock == 1) {

    if (noSerial == false) {
      Serial.println("Enter first digit of passcode.");
      noSerial = true;
      pinCorrect = false;
    }
    if (SerialAvailable > 0) {
      myPin = myInput;
      //Serial.println(myPin);
      if (myPin == passOne) {
        lock = 2;
        noSerial = false;
        pinCorrect = true;
        return;
      }
      if (myPin != passOne) {
        Serial.println("Passcode incorrect, please try again.");
        lock = 0;
        noSerial = false;
        pinCorrect = false;
        noPythonSerial = false;
        return;
      }
    }
  }
  
  if (lock == 2) {
    if (noSerial == false && pinCorrect == true) {
      Serial.println("Enter second digit of passcode.");
      noSerial = true;
      pinCorrect = false;
    }
    if (SerialAvailable > 0) {
      myPin = myInput;
      if (myPin == passTwo) {
        lock = 3;
        noSerial = false;
        pinCorrect = true;
        return;
      }
      if (myPin != passTwo) {
        Serial.println("Passcode incorrect, please try again.");
        lock = 0;
        noSerial = false;
        pinCorrect = false;
        noPythonSerial = false;
        return;
      }
    }
  }

  if (lock == 3) {
    if (noSerial == false && pinCorrect == true) {
      Serial.println("Enter third digit of passcode.");
      noSerial = true;
      pinCorrect = false;
    }
    if (SerialAvailable > 0) {
      myPin = myInput;
      if (myPin == passThree) {
        lock = 4;
        noSerial = false;
        pinCorrect = true;
        return;
      }
      if (myPin != passThree) {
        Serial.println("Passcode incorrect, please try again.");
        lock = 0;
        noSerial = false;
        pinCorrect = false;
        noPythonSerial = false;
        return;
      }
    }
  }
  
  if (lock == 4) {
    if (noSerial == false && pinCorrect == true) {
      Serial.println("Enter fourth digit of passcode.");
      noSerial = true;
      pinCorrect = false;
    }
    
    if (SerialAvailable > 0) {
      myPin = myInput;
      if (myPin == passFour) {
        Serial.println("Passcode correct, system locked.");
        if (sysStatus == 1) {
          prevStatus = 1;
        }
        if (sysStatus == 3) {
          prevStatus = 3;
        }
        sysStatus = 2;
        lock = 0;
        noMessage = false;
        noRefresh = false;
        noSerial = false;
        pinCorrect = false;
        noPythonSerial = false;
        return;
      }
      if (myPin != passFour) {
        Serial.println("Passcode incorrect, please try again.");
        lock = 0;
        noSerial = false;
        pinCorrect = false;
        noPythonSerial = false;
        return;
      }
    }
  }
  if (normal == 1) {
    if (noSerial == false) {
      Serial.println("Enter first digit of passcode.");
      noSerial = true;
      pinCorrect = false;
    }
    if (SerialAvailable > 0) {
      myPin = myInput;
      if (myPin == passOne) {
        normal = 2;
        noSerial = false;
        pinCorrect = true;
        return;
      }
      if (myPin != passOne) {
        Serial.println("Passcode incorrect, please try again.");
        normal = 0;
        noSerial = false;
        pinCorrect = false;
        noPythonSerial = false;
        return;
      }
    }
  }
  if (normal == 2) {
    if (noSerial == false && pinCorrect == true) {
      Serial.println("Enter second digit of passcode.");
      noSerial = true;
      pinCorrect = false;
    }
    if (SerialAvailable > 0) {
      myPin = myInput;
      if (myPin == passTwo) {
        normal = 3;
        noSerial = false;
        pinCorrect = true;
        return;
      }
      if (myPin != passTwo) {
        Serial.println("Passcode incorrect, please try again.");
        normal = 0;
        noSerial = false;
        pinCorrect = false;
        noPythonSerial = false;
        return;
      }
    }
  }
  if (normal == 3) {
    if (noSerial == false && pinCorrect == true) {
      Serial.println("Enter third digit of passcode.");
      noSerial = true;
      pinCorrect = false;
    }
    if (SerialAvailable > 0) {
      myPin = myInput;
      if (myPin == passThree) {
        normal = 4;
        noSerial = false;
        pinCorrect = true;
        return;
      }
      if (myPin != passThree) {
        Serial.println("Passcode incorrect, please try again.");
        normal = 0;
        noSerial = false;
        pinCorrect = false;
        noPythonSerial = false;
        return;
      }
    }
  }
  if (normal == 4) {
    if (noSerial == false && pinCorrect == true) {
      Serial.println("Enter fourth digit of passcode.");
      noSerial = true;
      pinCorrect = false;
    }
    if (SerialAvailable > 0) {
      myPin = myInput;
      if (myPin == passFour) {
        Serial.println("Passcode correct, system in normal operation.");
        normal = 0;
        noSerial = false;
        if (sysStatus == 2) {
          prevStatus = 2;
        }
        if (sysStatus == 3) {
          prevStatus = 3;
        }
        sysStatus = 1;
        normal = 0;
        noMessage = false;
        noRefresh = false;
        pinCorrect = false;
        noPythonSerial = false;
        return;
      }
      if (myPin != passFour) {
        Serial.println("Passcode incorrect, please try again.");
        normal = 0;
        noSerial = false;
        pinCorrect = false;
        noPythonSerial = false;
        return;
      }
    }
  }
  //Unlock mode
  if (unlock == 1) {
    if (noSerial == false) {
      Serial.println("Enter first digit of passcode.");
      noSerial = true;
      pinCorrect = false;
    }
    if (SerialAvailable > 0) {
      myPin = myInput;
      if (myPin == passOne) {
        unlock = 2;
        noSerial = false;
        pinCorrect = true;
        return;
      }
      if (myPin != passOne) {
        Serial.println("Passcode incorrect, please try again.");
        unlock = 0;
        noSerial = false;
        pinCorrect = false;
        noPythonSerial = false;
        return;
      }
    }
  }
  if (unlock == 2) {
    if (noSerial == false && pinCorrect == true) {
      Serial.println("Enter second digit of passcode.");
      noSerial = true;
      pinCorrect = false;
    }
    if (SerialAvailable > 0) {
      myPin = myInput;
      if (myPin == passTwo) {
        unlock = 3;
        noSerial = false;
        pinCorrect = true;
        return;
      }
      if (myPin != passTwo) {
        Serial.println("Passcode incorrect, please try again.");
        unlock = 0;
        noSerial = false;
        pinCorrect = false;
        noPythonSerial = false;
        return;
      }
    }
  }
  if (unlock == 3) {
    if (noSerial == false && pinCorrect == true) {
      Serial.println("Enter third digit of passcode.");
      noSerial = true;
      pinCorrect = false;
    }
    if (SerialAvailable > 0) {
      myPin = myInput;
      if (myPin == passThree) {
        unlock = 4;
        noSerial = false;
        pinCorrect = true;
        return;
      }
      if (myPin != passThree) {
        Serial.println("Passcode incorrect, please try again.");
        unlock = 0;
        noSerial = false;
        pinCorrect = false;
        noPythonSerial = false;
        return;
      }
    }
  }
  if (unlock == 4) {
    if (noSerial == false && pinCorrect == true) {
      Serial.println("Enter fourth digit of passcode.");
      noSerial = true;
      pinCorrect = false;
    }
    if (SerialAvailable > 0) {
      myPin = myInput;
      if (myPin == passFour) {
        Serial.println("Passcode correct, system unlocked.");
        if (sysStatus == 1) {
          prevStatus = 1;
        }
        if (sysStatus == 2) {
          prevStatus = 2;
        }
        sysStatus = 3;
        unlock = 0;
        noMessage = false;
        noRefresh = false;
        noSerial = false;
        pinCorrect = false;
        noPythonSerial = false;
        return;
      }
      if (myPin != passFour) {
        Serial.println("Passcode incorrect, please try again.");
        unlock = 0;
        noSerial = false;
        pinCorrect = false;
        noPythonSerial = false;
        return;
      }
    }
  }
  /* sysStatus Codes
   *  1: Normal
   *  2: Lock
   *  3: Unlock
   */
   
  if (sysStatus == 1 && prevStatus == 2 && noRefresh == false) {
    rfidOn = true;
    lcd.clear();
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Waiting for card");
    noRefresh = true;
    if (noMessage == false) {
       Wire.beginTransmission(9);
       Wire.write(sNormal);
       Wire.endTransmission();
       noMessage = true;
    }
  }
  if (sysStatus == 1 && prevStatus == 3 && noRefresh == false) {
    rfidOn = true;
    lcd.clear();
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Waiting for card");
    myStepper.step(-stepsPerRevolution);
    noRefresh = true;
    if (noMessage == false) {
      Wire.beginTransmission(9);
      Wire.write(sNormal);
      Wire.endTransmission();
      noMessage = true;
    }
  }
  if (sysStatus == 2 && prevStatus == 1 && noRefresh == false) {
    rfidOn = false;
    lcd.clear();
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("*System  Locked*");
    lcd.setCursor(0, 1);
    lcd.print("****RFID OFF****");
    noRefresh = true;
    if (noMessage == false) {
      Wire.beginTransmission(9);
      Wire.write(sLock);
      Wire.endTransmission();
      noMessage = true;
    }
  }
  if (sysStatus == 2 && prevStatus == 3 && noRefresh == false) {
    rfidOn = false;
    lcd.clear();
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("*System  Locked*");
    lcd.setCursor(0, 1);
    lcd.print("****RFID OFF****");
    myStepper.step(-stepsPerRevolution);
    noRefresh = true;
    if (noMessage == false) {
      Wire.beginTransmission(9);
      Wire.write(sLock);
      Wire.endTransmission();
      noMessage = true;
    }
  }
  if (sysStatus == 3 && prevStatus == 1 && noRefresh == false) {
    rfidOn = false;
    lcd.clear();
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("****Unlocked****");
    lcd.setCursor(0, 1);
    lcd.print("****RFID OFF****");
    myStepper.step(stepsPerRevolution);
    noRefresh = true;
    if (noMessage == false) {
      
      Wire.beginTransmission(9);
      Wire.write(sUnlock);
      Wire.endTransmission();
      noMessage = true;
    }
  }
  if (sysStatus == 3 && prevStatus == 2 && noRefresh == false) {
    rfidOn = false;
    lcd.clear();
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("****Unlocked****");
    lcd.setCursor(0, 1);
    lcd.print("****RFID OFF****");
    myStepper.step(stepsPerRevolution);
    noRefresh = true;
    if (noMessage == false) {
      Wire.beginTransmission(9);
      Wire.write(sUnlock);
      Wire.endTransmission();
      noMessage = true;
    }
  }
   
  if (!mfrc522.PICC_IsNewCardPresent()) 
  {
    // Serial.print("not new card");
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    // Serial.print("not read card");
    return;
  }
  // If sysStatus is not 1, disable rfid code.
  if (rfidOn == false) {
    return;
  }

  lcd.clear();
  lcd.begin(16, 2);
  lcd.print("Card UID :");
  String content= "";
  byte letter;
  // Serial.print("loop");
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
    lcd.setCursor(0, 1);
    lcd.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    lcd.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
    // Serial.print("in");
    //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    //Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  //Serial.println();
  lcd.clear();
  lcd.begin(16, 2);
  lcd.print(" ");
  content.toUpperCase();
  Serial.println(content.substring(1));

  if (content.substring(1) == "A0 81 2D A5") //Plz change to your cards UID
  {
    lcd.setCursor(0,1);
    lcd.print("Card 1(OK)");
    lcd.setCursor(0,0);
    lcd.print(content.substring(1));
    tone(piezoPin, 1000, 500);
    tone(piezoPin, 100, 500);
    
    myStepper.step(stepsPerRevolution);
    Wire.beginTransmission(9);
    Wire.write(sOpen);
    Wire.endTransmission();
    

    delay(10000);
    myStepper.step(-stepsPerRevolution);
    Wire.beginTransmission(9);
    Wire.write(sNormal);
    Wire.endTransmission();
    lcd.clear();
    noRefresh = false;
    setup();
  }
  else if (content.substring(1) == "29 3F 75 63")
  {
    lcd.setCursor(0,1);
    lcd.print("Card 2(OK)");
    lcd.setCursor(0,0);
    lcd.print(content.substring(1));
    tone(piezoPin, 1000, 500);
    tone(piezoPin, 100, 500);
    
    myStepper.step(stepsPerRevolution);
    Wire.beginTransmission(9);
    Wire.write(sSmall);
    Wire.endTransmission();

    delay(10000);
    myStepper.step(-stepsPerRevolution);
    Wire.beginTransmission(9);
    Wire.write(sNormal);
    Wire.endTransmission();
    lcd.clear();
    noRefresh = false;
    setup();
  }
  /* else if (content.substring(1) == "")
   *  {lcd.setCursor(0,1);
    lcd.print("Card 3(OK)");
    lcd.setCursor(0,0);
    lcd.print(content.substring(1));
    tone(piezoPin, 1000, 500);
    tone(piezoPin, 100, 500);
    myStepper.step(stepsPerRevolution);

    delay(5000);
    myStepper.step(-stepsPerRevolution);
    lcd.clear();
    setup();
    }
   */
   /* else if (content.substring(1) == "")
   *  {lcd.setCursor(0,1);
    lcd.print("Card 4(OK)");
    lcd.setCursor(0,0);
    lcd.print(content.substring(1));
    tone(piezoPin, 1000, 500);
    tone(piezoPin, 100, 500);
    myStepper.step(stepsPerRevolution);

    delay(5000);
    myStepper.step(-stepsPerRevolution);
    lcd.clear();
    setup();
    }
   */
  else {
    lcd.setCursor(0, 1);
    lcd.print("Unknown Card");
    lcd.setCursor(0, 0);
    lcd.print(content.substring(1));
    Wire.beginTransmission(9);
    Wire.write(sIncorrect);
    Wire.endTransmission();
    delay(5000);
    lcd.clear();
    Wire.beginTransmission(9);
    Wire.write(sRestore);
    Wire.endTransmission();
    noRefresh = false;
    setup();
  }
} 
