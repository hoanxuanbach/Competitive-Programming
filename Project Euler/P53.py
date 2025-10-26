
n = 100 

fac = [1 for i in range(n+1)]

for i in range(1,n+1):
    fac[i]=fac[i-1]*i

cnt = 0
for i in range(1,n+1):
    for j in range(1,i):
        val = fac[i]//fac[j]//fac[i-j]
        if(val>1000000): cnt+=1

print(cnt)