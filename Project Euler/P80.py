import math
from decimal import Decimal, getcontext
getcontext().prec = 200 

n = int(input())
res = 0

for X in range(2,n+1):
    x = X
    d = int(math.sqrt(x))
    if(d*d==X):
        continue

    k = 100
    while(d):
        res+=d%10
        d//=10
        k-=1
    
    d = int(math.sqrt(x))
    for i in range(k):
        x*=100
        d*=10
        while((d+1)*(d+1)<=x):
            res+=1
            d+=1

print(res)