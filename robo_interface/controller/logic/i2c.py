from smbus2 import SMBus

class I2CBridge():

    def __init__(self):

        # SMBus
        self.DEVICE_BUS = 1
        self.DEVICE_ADDR = 0x08
        self.bus = SMBus(self.DEVICE_BUS)

        # Movement constants
        self.MOVEMENT = 0x00
        self.FORWARD = 0x01
        self.BACKWARD = 0x02
        self.LEFT = 0x03
        self.RIGHT = 0x04
        self.STOP = 0x05

        self.DIRECTIONS = {
            "forward": self.FORWARD,
            "backward": self.BACKWARD,
            "left": self.LEFT,
            "right": self.RIGHT,
            "stop": self.STOP
        }

    def status(self):
        self.bus.read_byte(self.DEVICE_ADDR)

    def move(self, direction, speed):

        if direction not in self.DIRECTIONS:
            raise Exception("Unknown movement command")
            
        if speed > 30 or speed < 0:
            raise Exception("Excessive speed!")

        self.bus.write_i2c_block_data(self.DEVICE_ADDR, self.MOVEMENT, [self.DIRECTIONS[direction], speed])
        