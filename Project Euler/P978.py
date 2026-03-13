import math
from decimal import Decimal, getcontext
getcontext().prec = 50

n = int(input())

f = [0 for i in range(n+1)]
g = [0 for i in range(n+1)]

f[1]=g[1]=1
for i in range(2,n+1):
    f[i]=f[i-1]+f[i-2]
    g[i]=g[i-1]+g[i-2]*3

k = Decimal(f[n]-1).sqrt()
k = k*k*k

S = g[n]-3*f[n]+2
S = Decimal(S)/k

print(S)

