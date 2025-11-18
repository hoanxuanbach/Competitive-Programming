import math
from decimal import Decimal, getcontext
getcontext().prec = 40

N = 5000

def cal(x):
    res = 0 
    T = Decimal(1)
    for k in range(N):
        res+=T*(900-3*(k+1))
        T*=x

    return res

L = Decimal(0) 
R = Decimal(2)

D = Decimal(1)
for i in range(12):
    D/=Decimal(10)

S = -600000000000
while L+D<=R:
    X = (L+R)/2
    if(cal(X)<S): R=X
    else: L=X

print((L+R)/2)


