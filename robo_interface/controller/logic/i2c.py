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

    def status(self):
        self.bus.read_byte(self.DEVICE_ADDR)

    def move(self, direction, speed):
        direction_keys = {
            "forward": self.FORWARD,
            "backward": self.BACKWARD,
            "left": self.LEFT,
            "right": self.RIGHT,
            "stop": self.STOP
        }

        if direction not in direction_keys:
            raise Exception("Unknown movement command")
            
        if (speed > 127):
            raise Exception("Excessive speed!")

        self.bus.write_i2c_block_data(self.DEVICE_ADDR, self.MOVEMENT, [direction_keys[direction], speed])
        