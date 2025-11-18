import math
from decimal import Decimal, getcontext
getcontext().prec = 20

N = int(input())
res = 0

k = 2

for n in range(5,N+1):
    //print(n,flush=True)
    x = 1 
    d = Decimal(n).ln()

    while k <= n:
        v = (Decimal(n).ln()-Decimal(k).ln())*k   
        if v > d:
            d = v
            x = k
            k += 1
        else:
            break

    if(k>2): k-=1

    x = x//math.gcd(n,x)
    while x%2 == 0:
        x/=2
    while x%5 == 0:
        x/=5

    if x>1 :
        res+=n
    else:
        res-=n    
print(res)