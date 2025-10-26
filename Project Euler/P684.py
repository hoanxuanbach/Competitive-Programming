mod = 1000000007

def f(x):
    d = (x-1)%9+1
    n = (x-d)//9

    S = (d*(d+3)//2)*pow(10,n,mod)%mod
    T = (pow(10,n,mod)+mod-1)%mod
    T = T*pow(9,mod-2,mod)%mod
    S = (S+54*T)%mod
    return (S+mod-x%mod)%mod

A = 0
B = 1
res = 0
for i in range(1,90):
    A,B=B,A
    B+=A

    res+=f(B)
    res%=mod

print(res)