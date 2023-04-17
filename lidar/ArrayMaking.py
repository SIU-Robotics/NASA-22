from asyncore import loop
import math, sys
from re import X

print("180 / pi Degrees is equal to Radians : ", end ="")
print (math.radians(180 / math.pi))

matrix = [[1 for i in range(15)] for j in range(15)]

Radius = 10 #in milimeters
Degs = 90
Radians = math.radians(Degs)

x = Radius * math.cos(Radians)
y = Radius * math.sin(Radians)

print("x is equal to", end ="")
print(x)

print("y is equal to", end ="")
print(y)

x = math.floor(x)
y = math.floor(y)

print(x)
print(y)

matrix[x][y] = 0

print(matrix)


