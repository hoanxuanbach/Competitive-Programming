
cnt=0
for d in range(1,10):
    x = d
    k = 1
    while(len(str(x))==k):
        cnt+=1
        x*=d
        k+=1

print(cnt)