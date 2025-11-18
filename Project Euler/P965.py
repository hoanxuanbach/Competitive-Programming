import math
from decimal import Decimal, getcontext
getcontext().prec = 40

N = int(input())

X = []

X.append((Decimal(0),1,0))

X.append((Decimal(1),0,0))

for i in range(1,N+1):
    print(i)
    for j in range(1,i):
        if(math.gcd(i,j)==1):
            X.append((Decimal(j)/Decimal(i),i,j))

X.sort()

res = Decimal(0)
print("start")

for i in range(len(X)-1):
    if(i%1000==0): print(i)
    l = X[i][0]
    r = X[i+1][0]
    val=X[i][1]*Decimal(r*r-l*l)/Decimal(2)-X[i][2]*(r-l)
    res+=val
    #print(X[i][0],X[i][1],X[i][2],X[i+1][1],val)

print(res)
