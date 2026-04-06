from scipy.special import gammainc
import math 

N = int(input())
R = 0.75 

l,r = 0,10**20

for _ in range(100):
    m = (l+r)*0.5
    if gammainc(N,m) < R :
        l = m
    else :
        r = m

print(l/math.log(10))