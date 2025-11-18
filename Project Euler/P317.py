from math import pi

v = 20
h = 100
g = 9.81

res = pi*((2*g*v*h + v*v*v)**2) / (4*g*g*g)

print(res)