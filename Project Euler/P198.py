import math


N = 10**8
T = 100
res = 0

S = [(0,1,1,T//2)]

while len(S) > 0:
    a,b,c,d = S[-1]
    S.pop()

    x = a*d+b*c
    y = b*d*2

    if(y>N):
        continue
    
    p = a+c
    q = b+d
    
    if(x*T<y):
        res+=1

    if a == 0 and b == 1 and c == 1 and d == N//100:
        res+=N//2-d
        break

    
    
    S.append((a,b,p,q))
    S.append((p,q,c,d))

print(res)
