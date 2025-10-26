cnt = 0

n = 1000000

p = [0 for i in range(n)]
for i in range(2,n):
    if(p[i]==0):
        for j in range(2*i,n,i): p[j]=1

for i in range(2,n):
    if(p[i]): continue
    k=0
    x=1

    while(x*10<=i): 
        x*=10
        k+=1
    
    d=i
    check=True
    for j in range(k):
        a=d%10
        d//=10
        d+=a*x
        if(p[d]): check=False
    
    if(check): 
        cnt+=1


print(cnt)