#!/usr/bin/env python3

import sys
import serial
import readline


device = sys.argv[1]


readline.clear_history()
client = serial.Serial(device, 9600)
while True:
    s = input("$ ")
    if s == "quit":
        break
    client.write((s + "\n").encode())
    data = client.readline()
    print(data.decode(), end="")
