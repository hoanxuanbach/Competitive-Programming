from decimal import Decimal, getcontext
getcontext().prec = 10

X=Decimal(1)

for i in range(41,61): X*=i
for i in range(51,71): X/=i

print(7*(1-X))
