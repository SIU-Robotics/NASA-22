from rplidar import RPLidar
import math
import numpy as np
from matplotlib import pyplot as plt
import matplotlib.pylab as pylab

params = {'legend.fontsize': 'medium',
          'figure.figsize': (15, 5),
         'axes.labelsize': 'x-large',
         'axes.titlesize':'x-large',
         'xtick.labelsize':'x-large',
         'ytick.labelsize':'x-large'}

pylab.rcParams.update(params)

lidar = RPLidar('COM3')

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

except KeyboardInterrupt:
    plt.figure()
    plt.imshow(matrix)
    plt.ylim(-0.5, 99.5) #to show no blank spaces
    plt.xlim(-0.5, 99.5) #to show no blank spaces

    plt.show()
    print('printing...')

try:
    while True:
        continue
except KeyboardInterrupt:
    print("stopping")
lidar.stop()
lidar.stop_motor()
lidar.disconnect()