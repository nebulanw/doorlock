#!/usr/bin/python
# -*- coding: utf-8 -*-
# RFID Client for Raspberry Pis connnected to a CrowPi
import socket
import Adafruit_CharLCD as LCD

# Connect to socket server
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('193.168.1.89', 8081))

# Setup LCD


# Initialize the LCD using the pins above.
lcd = LCD.Adafruit_CharLCDBackpack(address=0x21)
lcd.set_backlight(0)
lcd.clear()

print("RFID Client")
print("[INFO] Connected to server.")

# Main loop
# Four spaces:
# Eight spaces:        
while True:
    msg = client.recv(1024)
    msg.decode("utf-8")
    msg = str(msg.decode("utf-8"))
    #print(msg)
    if msg == "Normal":
        lcd.clear()
        lcd.message("Waiting for card")
    elif msg == "A1":
        lcd.clear()
        lcd.message("16012945165169\nCard A1")
    elif msg == "A2":
        lcd.clear()
        lcd.message("4163117990\nCard A2")
    elif msg == "C1":
        lcd.clear()
        lcd.message("10310717157158\nCard C1")
    elif msg == "C2":
        lcd.clear()
        lcd.message("135248768297\nCard C2")
