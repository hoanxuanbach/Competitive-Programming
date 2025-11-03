import math

from decimal import Decimal, getcontext
getcontext().prec = 1005

X = int(input())
N = int(input())

for i in range(N): X*=100
X = int(Decimal(X).sqrt())


S = 0
for i in range(N):
    S+=X%10
    X//=10

print(S)