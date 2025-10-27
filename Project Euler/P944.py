
N = pow(10,14)

S = pow(10,7)

mod = 1234567891

res = N*(N+1)//2*pow(2,N-1,mod)%mod

for i in range(1,S):
    l=N//(i+1)
    r=(N//i)
    res-=(r-l)*(r+l+1)//2*pow(2,N-i,mod)%mod

for i in range(1,N//S+1):
    x=N//i
    res-=i*pow(2,N-x,mod)

res=(res%mod+mod)%mod
print(res)