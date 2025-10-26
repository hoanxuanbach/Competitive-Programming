n = 1000
mod = 10000000000

s = 0
for i in range(1,n+1): s=(s+pow(i,i,mod))%mod
print(s)