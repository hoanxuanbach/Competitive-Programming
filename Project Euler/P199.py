import math
from decimal import Decimal, getcontext
getcontext().prec = 20

def area(x):
    return x*x

def dfs(k1,k2,k3,d):
    if d == 0:
        return 0
    k4 = k1+k2+k3+Decimal(2)*((k1*k2+k2*k3+k3*k1).sqrt())
    res = area(Decimal(1)/k4)
    return res+dfs(k1,k2,k4,d-1)+dfs(k1,k3,k4,d-1)+dfs(k2,k3,k4,d-1)

N = 10
K = Decimal(3)-Decimal(2)*(Decimal(3).sqrt())
R = Decimal(-1)/K

res = Decimal(3) + dfs(Decimal(1),Decimal(1),K,N)*3 + dfs(Decimal(1),Decimal(1),Decimal(1),N)
res = Decimal(1) - res/area(R)

print(res)