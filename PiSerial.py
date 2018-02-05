import serial
import random

port = serial.Serial("/dev/ttyAMA0", baudrate=9600, timeout=3.0)

colors = []

for c in range(5):
    colorRGB = []
    colorRGB.append(random.randint(0, 255)) #R
    colorRGB.append(random.randint(0, 255)) #G
    colorRGB.append(random.randint(0, 255)) #B

for c in colors:
    for rgb in c:
        port.write(rgb);
        rcv = port.read(1);
        pritn(rcv)
