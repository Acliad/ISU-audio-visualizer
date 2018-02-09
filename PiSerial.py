import time
import serial
import random

port = serial.Serial("/dev/ttyAMA0", baudrate=115200, timeout=3.0)

colorRGB = []
startTime = time.time()

for c in range(250):
    colorRGB.append(random.randint(0, 255)) #B
    colorRGB.append(random.randint(0, 255)) #G
    colorRGB.append(random.randint(0, 255)) #R
print((time.time() - startTime)*1000)

for c in colorRGB:
    port.write(chr(c));
#    rcv = port.read(1);
#    print(rcv)

# Reads each digit as one byte
port.read(1)
print((time.time() - startTime) * 1000)
