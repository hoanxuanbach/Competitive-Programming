N = 10**7
M = 10**9 + 7

f = [0]*N
for i in range(2,N):
    if(f[i]==0):
        for j in range(i,N,i):
            f[j]=i
    

d = [0]*N 
for x in range(1,N):
    if(x%10000==0):
        print("first ",x)
    for i in range(x+1,N,x):
        if(f[i]==i and d[i]==0):
            if(pow(M,x,i)==1):
                d[i]=x


cnt = [0]*N 
for i in range(1,N):
    if(f[i]==i):
        cur = N
        while(cur):
            cur//=i
            cnt[i]+=cur

k = [0]*N 

dd = [0]*N 

s2 = M+1
s = 0 
while(s2%2==0):
    s2/=2
    s+=1

dd[2]=max(0,cnt[2]-s)
for i in range(3,N):
    if(i%10000==0):
        print("second ",i)

    if(f[i]==i):
        cur = i 
        k[i] = 1
        while(pow(M,d[i],cur*i)==1):
            cur*=i
            k[i]+=1

        dd[i]=max(0,cnt[i]-k[i])

        cur = d[i]
        while(cur>1):
            j=f[cur]
            num=0 
            while(cur%j==0):
                num+=1
                cur//=j

            dd[j]=max(dd[j],num)

res = 1
for i in range(1,N):
    if(dd[i]):
        res=res*pow(i,dd[i],M)%M 

print(res)
    


        

