from smbus2 import SMBus

DEVICE_BUS = 1
DEVICE_ADDR = 0x08
bus = SMBus(DEVICE_BUS)

keepgoing = 1
num = 0

while keepgoing == 1:
    print("1) Turn on LED\n2) Turn off LED\n3) Quit\n\nEnter a command: ")
    num = input()
    num = bytes(num, 'ascii')
    bus.write_i2c_block_data(DEVICE_ADDR, 0x2, [0x103, 0x00])
