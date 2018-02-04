import serial
import random

port = serial.Serial("/dev/ttyAMA0", baudrate=9600, timeout=3.0)

colors = []

for c in range(5):
    colors.append(random.randint(0, 16777215))

for c in colors:
    port.write(123)
    rcv = port.read(1)
    print(rcv)
