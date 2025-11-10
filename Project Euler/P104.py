import math

phi = (1+5**0.5)/2

mod = 10**9
n = 2
A = 1
B = 1
F = "123456789"

while(True):
    n+=1
    A,B=B,(A+B)%mod
    
    X = n*math.log10(phi)-math.log10(5)/2
    X = X-math.floor(X)
    Z = int(10**(X+8))

    sB = str(B)
    sZ = str(Z)
    sB = ''.join(sorted(sB))
    sZ = ''.join(sorted(sZ))
    if(sB==F and sZ==F):
        break

print(n)