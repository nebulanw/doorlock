#!/usr/bin/python
# -*- coding: utf-8 -*-
# RFID Client for Raspberry Pis connected to a standard breadboard
import socket
import Adafruit_CharLCD as LCD

# Connect to socket server
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('193.168.1.148', 8081))

# Setup LCD
# Raspberry Pi pin configuration:
lcd_rs        = 25  # Note this might need to be changed to 21 for older revision Pi's.
lcd_en        = 24
lcd_d4        = 23
lcd_d5        = 17
lcd_d6        = 18
lcd_d7        = 22
lcd_backlight = 4


# Define LCD column and row size for 16x2 LCD.
lcd_columns = 16
lcd_rows    = 2


# Initialize the LCD using the pins above.
lcd = LCD.Adafruit_CharLCD(lcd_rs, lcd_en, lcd_d4, lcd_d5, lcd_d6, lcd_d7,
                           lcd_columns, lcd_rows, lcd_backlight)
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
