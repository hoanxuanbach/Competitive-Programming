
N = 2000000
mod = 1000000

f = [0]*N
g = [0]*N 
sf = [0]*N 
sg = [0]*N

f[0]=sf[0]=1
for i in range(1,N):
    if(i>=2): f[i]+=f[i-2]
    if(i>=4): g[i]+=f[i-4]
    if(i>=6): f[i]+=sf[i-6]
    if(i>=2): g[i]+=sg[i-2]

    if(i==2): g[i]+=1
    else: f[i]+=1

    if(i>=2):
        sg[i]=sg[i-2]+g[i]
        sf[i]=sf[i-2]+f[i]

    f[i]%=mod
    g[i]%=mod
    sf[i]%=mod
    sg[i]%=mod

    if(g[i]==0):
        print(i)
