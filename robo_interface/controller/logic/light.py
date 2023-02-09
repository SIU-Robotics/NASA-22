from smbus2 import SMBus

DEVICE_BUS = 1
DEVICE_ADDR = 0x08
bus = SMBus(DEVICE_BUS)

def turnOn():
    bus.write_byte(DEVICE_ADDR, 0x66)

def turnOff():
    bus.write_byte(DEVICE_ADDR, 0x62)