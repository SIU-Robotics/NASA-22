
from smbus2 import SMBus

DEVICE_BUS = 1
DEVICE_ADDR = 0x08
bus = SMBus(DEVICE_BUS)

keepgoing = 1
num = 0

while keepgoing == 1:
    print("1) Turn on LED\n2) Turn off LED\n3) Quit\n\nEnter a command: ")
    num = input()
    bus.write_byte(DEVICE_ADDR, NUM)
    #if num == 1:
    #    bus.write_byte(DEVICE_ADDR, 0x01)
    #elif num == 2:
    #    bus.write_byte(DEVICE_ADDR, 0x00)
    #else:
    #    keepgoing = 0
    #    break
