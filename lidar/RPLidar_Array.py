from rplidar import RPLidar
from asyncore import loop
from logging import exception
import math, sys
from re import X

lidar = RPLidar('/dev/ttyUSB0')

matrix = [[1 for k in range(100)] for l in range(100)] #first range is how many numbers inside arrays, second range is how many arrays

quality = 0
angle = 0
distance = 0

info = lidar.get_info()
print(info)

health = lidar.get_health()
print(health)
try:
    for i, scan in enumerate(lidar.iter_scans()):
        print('%d: Got %d measurements' % (i, len(scan)))

        scanNum = len(scan)

        j = 0
        while j < scanNum:
            quality, angle, distance = scan[j]

            radians = math.radians(angle)

            x = distance * math.cos(radians) #converts from polar to xy
            y = distance * math.sin(radians)

            x = x / 100
            y = y / 100

            x = math.floor(x)
            y = math.floor(y)

            matrix[x][y] = 0

            j = j + 1


        print('Press Ctrl+C to stop.')
except KeyboardInterrupt:
    print('stopping')

lidar.stop()
lidar.stop_motor()
lidar.disconnect()