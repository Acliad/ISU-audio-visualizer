import time
import serial
import random

port = serial.Serial("/dev/ttyAMA0", baudrate=115200, timeout=3.0)

strip_length = 25
head = 1
tail = head - 5 #5 is numLEDs

while (tail < strip_length):
    pixels = []

    for i in range(strip_length):
        color_components = []
        if (i <= head and i >= tail):
            color_components.append(0) # R
            color_components.append(0) # G
            color_components.append(100) # B
        else:
            color_components.append(0)
            color_components.append(0)
            color_components.append(0)
        pixels.append(color_components)

    port.write(chr(254))

    for c in pixels:
        port.write(chr(c[0]))
        port.write(chr(c[1]))
        port.write(chr(c[2]))

    port.write(chr(255))

    head += 1
    tail += 1
    time.sleep(0.011)
