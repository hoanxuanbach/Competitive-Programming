import math
from decimal import Decimal, getcontext
getcontext().prec = 40

n = 0 
x = 1000000000
X = Decimal(1)/Decimal(x)
S = Decimal(30.403243784)

mp = {}

while(x not in mp):
    print(n,x,flush=True)
    mp[x] = n
    n += 1
    fx = Decimal(x)*X
    x = math.floor(Decimal(2)**(S-fx*fx))

print(x,n,mp[x])

A = Decimal(681175878)
B = Decimal(1029461839)

res = (A+B)*X

print(res)