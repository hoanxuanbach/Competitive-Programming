import math

def pell(D):

    x = int(math.sqrt(D))
    if(x*x==D):
        return -1,-1
    
    m = 0
    d = 1
    a = x

    period = []
    seen = {}
    while True:
        m = d*a-m
        d = (D-m*m)//d 
        a = (x+m)//d 

        if((m,d) in seen):
            break
        
        seen[(m,d)] = True
        period.append(a)
    
    k = len(period)
    if(k%2==1):
        period *= 2
    period.pop()
    
    A = 0 
    B = 1
    k = len(period)
    for i in range(k-1,-1,-1):
        A+=period[i]*B
        A,B=B,A
    
    A+=x*B
    return A,B


N = 10**10

M = 0
while(2*M*(M+1)<=N):
     M+=1

M+=2

p = [0]*M
for i in range(2,M):
    if(p[i]==0):
        for j in range(i,M,i):
            p[j]=i

f = [1]*M
g = [1]*M

for i in range(1,M):
    x = i
    while(x>1):
        j = p[x]
        k = 0
        while(x%j==0):
            x//=j
            k+=1

        if(k&1):
            f[i]*=j

        g[i]*=j**(k//2)

S = set()
for m in range(1,M-1):
    D = f[m]*f[m+1]
    X,Y=pell(D)
    x,y=X,Y 

    T = D*g[m]*g[m+1]
    while(True):
        t = T*y 
        k = m*(x+1)+t 
        if(k>N*2):
            break
        n = (m+1)*(x-1)+t 
        if(n>=k and n%2==0 and k%2==0):
            S.add(k>>1)

        x,y = X*x+D*Y*y,X*y+Y*x 

print(sum(S))

