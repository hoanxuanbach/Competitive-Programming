from decimal import Decimal, getcontext
getcontext().prec = 20

N = 32

f = [Decimal(0)]*(N+1)

C = [[0]*(N+1) for _ in range(N+1)]

for i in range(N+1):
    C[i][0]=1
    for j in range(1,i+1):
        C[i][j]=C[i-1][j]+C[i-1][j-1]

for i in range(N-1,-1,-1):
    d = (2**(N-i)-1)
    f[i] = d+1
    for k in range(1,N-i+1):
        f[i]+=f[i+k]*C[N-i][k]
    f[i]/=d

print(f[0])
