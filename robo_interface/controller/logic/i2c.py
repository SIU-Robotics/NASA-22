from smbus2 import SMBus

# Movement variables
movement = 0x00
forward = 0x01
backward = 0x02

# Claw variables
claw = 0x03

class I2CBridge():


    def __init__(self):
        self.DEVICE_BUS = 1
        self.DEVICE_ADDR = 0x08
        self.bus = SMBus(self.DEVICE_BUS)

    def move(self, direction, speed):
        if (speed > 127):
            raise Exception("Excessive speed!")
        match direction:
            case 'forward':
                self.bus.write_i2c_block_data(self.DEVICE_ADDR, 0x3, [movement, forward, speed])
            case 'backward':
                self.bus.write_i2c_block_data(self.DEVICE_ADDR, 0x3, [movement, backward, speed])
            case _:
                raise Exception("Unknown movement command")


    def claw(self):
        self.bus.write_i2c_block_data(self.DEVICE_ADDR, 0x3, [claw])