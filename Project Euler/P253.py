
import math
from decimal import Decimal, getcontext
getcontext().prec = 50

n = int(input())

f = [0]*(n+1)

for M in range(1,n//2+1):
    dp = [[[[0 for _ in range(2)] for _ in range(2)] for _ in range(n+1)] for _ in range(n+1)]

    dp[0][0][0][0]=1
    for i in range(n):
        for x in range(min(i,M)+1):
            for a in range(2):
                for b in range(2):

                    T = dp[i][x][a][b]

                    if(x):
                        dp[i+1][x-1][a][b]+=T*(x-1)
                    
                    dp[i+1][x][a][b]+=T*(2*x-a-b)

                    dp[i+1][x+1][a][b]+=T*(x+1-a-b)

                    if(a==0):
                        dp[i+1][x+1][1][b]+=T
                        if(x):
                            dp[i+1][x][1][b]+=T

                    if(b==0):
                        dp[i+1][x+1][a][1]+=T
                        if(x):
                            dp[i+1][x][a][1]+=T


    f[M]=dp[n][1][1][1]

for i in range(n//2,0,-1):
    f[i]-=f[i-1]

S = 0
for i in range(1,n//2+1):
    S+=i*f[i]

S = Decimal(S)
for i in range(1,n+1):
    S/=Decimal(i)

print(S)