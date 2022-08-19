#!/usr/bin/env python3

import serial
import readline


readline.clear_history()
client = serial.Serial("/dev/tty.usbmodem141103", 9600)
while True:
    s = input("$ ")
    if s == "quit":
        break
    client.write((s + "\n").encode())
    data = client.readline()
    print(data.decode(), end="")
