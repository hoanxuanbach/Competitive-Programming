import math

N = 1000000000
period = 120

A = 0 
B = 1

for i in range(period):
    A,B=B,A
    B+=A

G = math.gcd(A,B-1)

def f(x):
    if(x >= N or x == 1): return 0
    a = 0 
    b = 1
    for i in range(period-1):
        a,b=b,a
        b=(b+a)%x
        if(a==0 and b==1): 
            return 0
    return 1

cnt = 0
for i in range(1,G+1):
    if(i*i>G): break
    if(G%i!=0): continue
    cnt+=f(i)*i
    if(i*i!=G): cnt+=f(G//i)*(G//i)

print(cnt)
