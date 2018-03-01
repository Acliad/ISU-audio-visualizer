import time
import serial
import random

port = serial.Serial("/dev/ttyAMA0", baudrate=115200, timeout=3.0)

colorRGB = []
startTime = time.time()

for c in range(250):
    colorRGB.append(random.randint(0, 253)) #B
    colorRGB.append(random.randint(0, 253)) #G
    colorRGB.append(random.randint(0, 253)) #R
print((time.time() - startTime)*1000)

port.write(chr(254))

for c in colorRGB:
    port.write(chr(c));
#    rcv = port.read(1);
#    print(rcv)

port.write(chr(255))

# Reads each digit as one byte
# port.read(1)
print((time.time() - startTime) * 1000)
