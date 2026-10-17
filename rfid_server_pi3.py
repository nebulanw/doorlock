#!/usr/bin/python
# -*- coding: utf-8 -*-
# RFID Security System Server V1
# Run on CrowPi
import socket
import signal
import time
import MFRC522
import Adafruit_CharLCD as LCD
import RPi.GPIO as GPIO
global screenRefresh
global delay
delay = 10
continue_reading = True
screenRefresh = True
#global msg
#msg = ''
# Socket server setup
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(('193.168.1.89', 8081))
server.listen(1024)

print("RFID Server")
# LCD Definition
# For GPIO LCDs
lcd = LCD.Adafruit_CharLCD(4, 24, 23, 17, 18, 22, 16, 2, 4)

# For CrowPi LCDs
#lcd_columns = 16
#lcd_rows = 2
#lcd = LCD.Adafruit_CharLCDBackpack(address=0x21)

# Define KeyboardInterrupt event
def end_read(signal, frame):
    global continue_reading
    continue_reading = False
    #server.shutdown()
    server.close()
    lcd.clear()
    lcd.set_backlight(1)
    GPIO.cleanup()
    print("[INFO] Program stopped.")

# RFID setup
signal.signal(signal.SIGINT, end_read)
MIFAREReader = MFRC522.MFRC522()

# Misc setup scripts
lcd.set_backlight(0)
lcd.clear()
#clients = []

# Setup buzzer
buzzer_pin = 5

#GPIO.setmode(GPIO.BCM)
GPIO.setup(buzzer_pin, GPIO.OUT)

# Wait for client to connect...
print("[INFO] Waiting for client...")
# Check for new client connections to server
conn, addr = server.accept()
conn.send(bytes("Normal", "utf-8"))
print("[INFO] Client is online.")
# Main function
while continue_reading:
    
    if screenRefresh == True:
        lcd.clear()
        lcd.message("Swipe Card")
        screenRefresh = False
    # Wait for card
    (status, TagType) = MIFAREReader.MFRC522_Request(MIFAREReader.PICC_REQIDL)
    if status == MIFAREReader.MI_OK:
        lcd.clear()
        #print("card detected")
    #lcd.clear()
    (status, uid) = MIFAREReader.MFRC522_Anticoll()
    if status == MIFAREReader.MI_OK:
        #print(uid)
        # Card A1
        #global uid
        if uid == [160, 129, 45, 165, 169]:
            # Print UID
            #print("Card read UID: %s,%s,%s,%s" % (uid[0], uid[1], uid[2], uid[3]))
            # standard key for rfid tags
            key = [0xFF,0xFF,0xFF,0xFF,0xFF,0xFF]
            # Select the scanned tag
            MIFAREReader.MFRC522_SelectTag(uid)
            # authenticate
            status = MIFAREReader.MFRC522_Auth(MIFAREReader.PICC_AUTHENT1A, 8, key, uid)
            # check if authenticated successfully, read the data
            if status == MIFAREReader.MI_OK:
                MIFAREReader.MFRC522_Read(8)
                MIFAREReader.MFRC522_StopCrypto1()
            #else:
                #print("[ERROR]Authentication error")
            
            lcd.clear()
            lcd.message("Card A1\nAccess Granted")
            conn.send("A1".encode("utf-8"))
            # Make buzzer sound
            GPIO.output(buzzer_pin, GPIO.HIGH)
            time.sleep(0.5)
            # Stop buzzer sound
            GPIO.output(buzzer_pin, GPIO.LOW)
            time.sleep(delay)
            screenRefresh = True
            conn.send("Normal".encode("utf-8"))
        elif uid == [41, 63, 117, 99, 0]:
            # Print UID
            #print("Card read UID: %s,%s,%s,%s" % (uid[0], uid[1], uid[2], uid[3]))
            # standard key for rfid tags
            key = [0xFF,0xFF,0xFF,0xFF,0xFF,0xFF]
            # Select the scanned tag
            MIFAREReader.MFRC522_SelectTag(uid)
            # authenticate
            status = MIFAREReader.MFRC522_Auth(MIFAREReader.PICC_AUTHENT1A, 8, key, uid)
            # check if authenticated successfully, read the data
            if status == MIFAREReader.MI_OK:
                MIFAREReader.MFRC522_Read(8)
                MIFAREReader.MFRC522_StopCrypto1()
            #else:
                #print("[ERROR] Authentication error")
            
            lcd.clear()
            lcd.message("Card A2\nAccess Granted")
            conn.send("A2".encode("utf-8"))
            # Make buzzer sound
            GPIO.output(buzzer_pin, GPIO.HIGH)
            time.sleep(0.5)
            # Stop buzzer sound
            GPIO.output(buzzer_pin, GPIO.LOW)
            time.sleep(delay)
            screenRefresh = True
            conn.send("Normal".encode("utf-8"))
        elif uid == [103, 107, 171, 57, 158]:
            # Print UID
            #print("Card read UID: %s,%s,%s,%s" % (uid[0], uid[1], uid[2], uid[3]))
            # standard key for rfid tags
            key = [0xFF,0xFF,0xFF,0xFF,0xFF,0xFF]
            # Select the scanned tag
            MIFAREReader.MFRC522_SelectTag(uid)
            # authenticate
            status = MIFAREReader.MFRC522_Auth(MIFAREReader.PICC_AUTHENT1A, 8, key, uid)
            # check if authenticated successfully, read the data
            if status == MIFAREReader.MI_OK:
                MIFAREReader.MFRC522_Read(8)
                MIFAREReader.MFRC522_StopCrypto1()
            #else:
                #print("[ERROR] Authentication error")
            
            lcd.clear()
            lcd.message("Card C1\nAccess Granted")
            conn.send("C1".encode("utf-8"))
            # Make buzzer sound
            GPIO.output(buzzer_pin, GPIO.HIGH)
            time.sleep(0.5)
            # Stop buzzer sound
            GPIO.output(buzzer_pin, GPIO.LOW)
            time.sleep(delay)
            screenRefresh = True
            conn.send("Normal".encode("utf-8"))
        elif uid == [135, 248, 76, 82, 97]:
            # Print UID
            #print("Card read UID: %s,%s,%s,%s" % (uid[0], uid[1], uid[2], uid[3]))
            # standard key for rfid tags
            key = [0xFF,0xFF,0xFF,0xFF,0xFF,0xFF]
            # Select the scanned tag
            MIFAREReader.MFRC522_SelectTag(uid)
            # authenticate
            status = MIFAREReader.MFRC522_Auth(MIFAREReader.PICC_AUTHENT1A, 8, key, uid)
            # check if authenticated successfully, read the data
            if status == MIFAREReader.MI_OK:
                MIFAREReader.MFRC522_Read(8)
                MIFAREReader.MFRC522_StopCrypto1()
            #else:
                #print("[ERROR] Authentication error")
            
            lcd.clear()
            lcd.message("Card C2\nAccess Granted")
            conn.send("C2".encode("utf-8"))
            # Make buzzer sound
            GPIO.output(buzzer_pin, GPIO.HIGH)
            time.sleep(0.5)
            # Stop buzzer sound
            GPIO.output(buzzer_pin, GPIO.LOW)
            time.sleep(delay)
            screenRefresh = True
            conn.send("Normal".encode("utf-8"))
        #else:
            #lcd.clear()
            #lcd.message("Unknown Card\nTry again")
            #conn.send(bytes("err"))
            #time.sleep(5)
            #conn.send(bytes("Normal"))