import math
from decimal import Decimal, getcontext
getcontext().prec = 50

n = int(input())

fac = [1 for _ in range(n+1)]
for i in range(1,n+1):
    fac[i]=fac[i-1]*i


C = [[0 for _ in range(n+1)] for _ in range(n+1)]

for i in range(n+1):
    C[i][0] = 1
    for j in range(1,i+1):
        C[i][j]=C[i-1][j-1]+C[i-1][j]

g = [0 for _ in range(n+1)]
for m in range(1,n+1):
    for k in range(m):
        val = C[m-1][k]*fac[m-k]
        if(k&1): g[m]-=val
        else: g[m]+=val


f = [[0 for _ in range(n+1)] for _ in range(n+1)]

for x in range(1,n+1):
    for m in range(1,x+1):
        f[x][m] = C[x-1][x-m]*g[m]

dp = [Decimal(0) for _ in range(n+1)]

for x in range(2,n+1):
    d = fac[x]-f[x][x]
    s = Decimal(fac[x]-1)
    for m in range(1,x):
        s += dp[m]*f[x][m]
    dp[x]=s/d

print(dp[n])





