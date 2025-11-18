import math


X = 10**12

N = 10**5

res = 0 
for n in range(1,N+1):
    print(n,flush = True)
    s = int(math.sqrt(n))
    if(s*s==n):
        continue
    

    a = s 
    b = 1
    c = s+1 
    d = 1

    while True : 
        p = a+c
        q = b+d

        if q > X : 
            break


        if n*q*q < p*p:
            c,d = p,q
        else:
            a,b = p,q
        

    if 4*n*((b*d)**2) < (c*b + a*d)**2 : 
        res+=b
    else: 
        res+=d

print(res)