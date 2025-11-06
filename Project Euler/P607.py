import math

from decimal import Decimal, getcontext
getcontext().prec = 20

def dist(A,B):
    xa,ya = A
    xb,yb = B
    return Decimal((xa-xb)**2+(ya-yb)**2).sqrt()

P = Decimal(100)/Decimal(2).sqrt()
S = (P-50)/2

res = Decimal(100)
D = 2000

for x in range(1,90*D):
    a = (Decimal(x)/D)*Decimal(math.pi)/180
    d = (S/Decimal(math.cos(a)))/10
    y = S*Decimal(math.tan(a))

    for k in range(9,4,-1):
        a = math.asin((k*math.sin(a))/(k+1))
        d+=(10/Decimal(math.cos(a)))/k
        y+=(10*Decimal(math.tan(a)))

    d+=dist((50+S,y),(P,P))/10
    res=min(res,d)

print(res)

