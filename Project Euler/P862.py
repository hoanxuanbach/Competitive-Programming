
def C(n,k):
    f = 1
    for i in range(1,n+1): f*=i
    for i in range(1,k+1): f//=i
    for i in range(1,n-k+1): f//=i

    return f

N = 12

p = [pow(10,i) for i in range(0,N+1)]

g = [0]*N

for i in range(N): 
    for j in range(N-i-1):
        g[i+j+1]+=C(i+j+1,i)*C(i+j+1,j)

for k in range(2,10):
    ng = [0]*N
    for i in range(N):
        for j in range(N-i):
            ng[i+j]+=g[i]*C(i+j,j)*C(i+j,j)
    g=ng

res = 0
for i in range(0,N-1):
    cnt = p[i]
    if(i): cnt-=p[i-1]
    if(i): cnt*=45
    else: cnt*=36
    res+=cnt*g[N-i-1]

print(res)


