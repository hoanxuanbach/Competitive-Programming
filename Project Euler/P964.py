
def P(n,k):
    cnt=1
    for i in range(k):
        cnt*=(n-i)
    return cnt

n = int(input())

n -= 1 

f = [0 for _ in range(1<<n)]

g = [[0 for _ in range(n+1)] for _ in range(1<<n)]

f[0] = 1
g[0][0] = 1

for mask in range(1,1<<n):
    m = mask
    x = 0 
    s = 0 
    k = 0

    for i in range(n):
        if(mask>>i&1):
            k+=1
            s+=i+1
            if(x==0):
                x=i+1

    if(k == 1):
        f[mask]=g[mask][1]=1
        continue
    
    m^=(1<<(x-1))   
    for d in range(1,k):
        f[mask]+=g[m][d]*(s+1)*P(x,d-1)


    for d in range(1,k+1):
        cur = m
        while(True):
            g[mask][d]+=g[cur][d-1]*f[mask^cur]
            if(cur==0):
                break
            cur=(cur-1)&m

res = f[(1<<n)-1]

N = n*(n+1)/2+1
D = 1
for k in range(1,n+1):
    D*=P(N,k+1)

res/=D
print(f"{res:.10e}")