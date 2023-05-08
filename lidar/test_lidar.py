from rplidar import RPLidar
import matplotlib.pyplot as plt
import numpy as np
import matplotlib.animation as animation

PORT_NAME = 'COM3'
DMAX = 4000
IMIN = 0
IMAX = 50

matrix = [[1 for k in range(100)] for l in range(100)]

def update_line(num, iterator, im):
    scan = next(iterator)
    arr = im.get_array()
    angle = np.array([(np.radians(meas[1])) for meas in scan])
    distance = np.array([meas[2] for meas in scan])
    for i in range(0, len(angle)):
        x = int(np.floor(distance[i] * np.cos(angle[i]) / 100))
        y = int(np.floor(distance[i] * np.sin(angle[i]) / 100))
        arr[x][y] = 0
        

    im.set_array(arr)

    return im,

def run():
    lidar = RPLidar(PORT_NAME)
    fig = plt.figure()

    im = plt.imshow(matrix, animated=True)

    iterator = lidar.iter_scans()
    ani = animation.FuncAnimation(fig, update_line,
        fargs=(iterator, im), interval=100)
    plt.show()
    lidar.stop()
    lidar.disconnect()

if __name__ == '__main__':
    run()