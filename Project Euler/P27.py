
n = 1000000
m = 1000

p = [1]*n

p[1] = 0

for i in range(2,n):
    if(p[i]):
        for j in range(2*i,n,i):
            p[j]=0

mx = 0
val = -1

for b in range(2,m):
    if(p[b]==0): continue
    for a in range(-b,m):
        n = 1
        while(n*n+a*n+b>0 and p[n*n+a*n+b]): n+=1

        if(n>mx):
            mx = n
            val = a*b

print(val)

