n = 10000

d = [int(0) for i in range(n+1)]

for i in range(1,n+1):
    for j in range(i*2,n+1,i):
        d[j]+=i

cnt=0

for i in range(1,n+1):
    if(d[i]>n or i==d[i]): continue
    elif(d[d[i]]==i): 
        print(i)
        cnt+=i

print(cnt)