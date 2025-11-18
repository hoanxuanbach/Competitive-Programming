import math
from decimal import Decimal, getcontext
getcontext().prec = 1000

n = 1000
X = Decimal(1000000000).ln()

k = (n//3)+1

F = Decimal(1)

while k <= n:
    ff = Decimal(2*k-(n-k))/Decimal(2*n)
    val = (Decimal(1)+2*ff).ln()*k+(Decimal(1)-ff).ln()*(n-k)

    if val >= X:
        F = ff
        break
    
    k+=1

print(k)

res = 0 
for i in range(k,n+1):
    prop = Decimal(1)
    for j in range(1,i+1):
        prop/=Decimal(j)
        prop*=Decimal(n-j+1)
    res+=prop

for j in range(n):
    res/=Decimal(2)

print(f"{res:.12f}")
