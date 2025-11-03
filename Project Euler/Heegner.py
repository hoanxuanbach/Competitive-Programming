import math
from decimal import Decimal, getcontext
getcontext().prec = 50

delta,val = 10**8,None
pi = Decimal('3.1415926535897932384626433832795028841971693993751')

for n in range(0,1001):
    d = int(math.sqrt(n))
    if(d*d==n):
        continue
    
    x = pi*Decimal(n).sqrt()
    A = (Decimal(x).exp()+Decimal(-x).exp())/Decimal(2)
    B = math.cos(math.pi*math.sqrt(n))

    dA = min(math.ceil(A)-A,A-math.floor(A))
    dB = min(math.ceil(B)-B,B-math.floor(B))

    if(dA<delta):
        delta=dA
        val=-n 

    if(dB<delta):
        delta=dB 
        val=n 

print(val) 
