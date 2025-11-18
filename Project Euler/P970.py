from decimal import Decimal, getcontext

getcontext().prec = 20

e = Decimal(1).exp()

#print(e)

'''
H(n) = sum(k = 0 -> n) (-1)^k*(n-k)^k/k!*e^(n-k)
'''

n = int(input())

res = 0
p = Decimal(n)

for k in range(n):
    if(k%1000==0):
        print(k,flush=True)

    if(k):
        p-=Decimal(k).ln()

    x=p+Decimal(n-k).ln()*k
    x=e**x
    
    if(k&1):
        res-=x
    else: 
        res+=x
    
    p-=1

print(res)

S = 0
while(S<(10**7)):
    res*=10
    d = int(res)%10
    if(d!=6):
        S=S*10+d

print(S)