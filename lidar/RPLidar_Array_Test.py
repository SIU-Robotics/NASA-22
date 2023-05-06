
from asyncore import loop
from logging import exception
import math, sys
from re import X
from tracemalloc import start
from pathfinding.core.diagonal_movement import DiagonalMovement
from pathfinding.core.grid import Grid
from pathfinding.finder.a_star import AStarFinder


matrix = [[1 for k in range(100)] for l in range(100)] #first range is how many numbers inside arrays, second range is how many arrays


quality = 0
angle = 0
distance = 0

scan = [(15, 0, 500),(15, 1.234, 900), (15, 2.567, 2000), (15, 5.345, 2500), (15, 7.142, 2300), (15, 8, 2300), (15, 9, 2300), (15, 10, 2300), (15, 11, 2300), (15, 12, 2300), (15, 13, 2300), (15, 14, 2300), (15, 15, 2300), (15, 16, 2300), (15, 17, 2300), (15, 18, 2300), (15, 19, 2300), (15, 20, 2300), (15, 21, 2300), (15, 22, 2300), (15, 23, 2300), (15, 24, 2300), (15, 25, 2300), (15, 26, 2300), (15, 27, 2300), (15, 28, 2300), (15, 29, 2300), (15, 30, 2300), (15, 31, 2300), (15, 32, 2300), (15, 33, 2300), (15, 34, 2300), (15, 35, 2300), (15, 36, 2300), (15, 37, 2300), (15, 38, 2300), (15, 39, 2300), (15, 40, 2300), (15, 41, 2300), (15, 42, 2300), (15, 43, 2300), (15, 44, 2300), (15, 45, 2300)]

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

grid = Grid(matrix=matrix)

inputx = 5
inputy = 10

targetx = inputx
targety = inputy

start = grid.node(50,50)
end = grid.node(targetx,targety)

finder = AStarFinder(diagonal_movement=DiagonalMovement.never)
path, runs = finder.find_path(start, end, grid)

print(matrix)

print('operations:', runs, 'path length:', len(path))
print(grid.grid_str(path=path, start=start, end=end))