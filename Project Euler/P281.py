import math 

ff = [1]

def fac(n):
    while(len(ff)<=n): 
        ff.append(ff[-1]*len(ff))
    return ff[n]

def h(n,m):
    return fac(n*m)//pow(fac(n),m)

def f(m,n):
    res=0
    for d in range(n*m):
        g=math.gcd(n*m,d)
        if(g%m==0):
            res+=h(g//m,m)

    return res//(n*m)

S = 10**15
res = 0 

for m in range(2,20):
    if(f(m,1)>S):
        break
    
    n = 1
    while(f(m,n)<=S):
        print(m,n)
        res+=f(m,n)
        n+=1

print(res)