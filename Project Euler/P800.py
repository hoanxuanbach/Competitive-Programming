from decimal import Decimal, getcontext
getcontext().prec = 10


N = 800800

X = Decimal(N).ln()*N

def f(a,b):
    S = Decimal(a).ln()*b+Decimal(b).ln()*a
    if(S<=X):
        return True
    return False 

M = 20000000

p = [1]*M
p[0]=p[1]=0
prime = []

for i in range(2,M):
    if(p[i]):
        if(i>2 and f(2,i)==False): break
        prime.append(i)
        for j in range(i*2,M,i):
            p[j]=0

cnt = 0

j = len(prime)-1
for i in range(len(prime)):
    if(j<=i): break
    while(i<j and f(prime[i],prime[j])==False): j-=1
    cnt+=j-i

print(cnt)

