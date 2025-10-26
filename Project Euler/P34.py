n = 10000000

fac = [int(i) for i in range(0,10)]

fac[0]=1
for i in range(1,10): fac[i]*=fac[i-1]

s = 0

for i in range(10,n):
    x = 0
    d = i
    while(d):
        k=d%10
        d//=10
        x+=fac[k]

    if(x==i): s+=i

print(s)