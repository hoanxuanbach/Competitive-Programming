import math
from decimal import Decimal, getcontext
getcontext().prec = 20


res = 0
for m in range(2,16):
    T = Decimal(1)
    for i in range(1,m+1):
        X = Decimal(i)*2/Decimal(m+1)
        T*=X**i
    res+=math.floor(T)

print(res)