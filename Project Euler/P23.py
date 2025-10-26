n = 28123

d = [int(0) for i in range(n+1)]

for i in range(1,n+1):
    for j in range(i*2,n+1,i):
        d[j]+=i

cnt=0

for i in range(1,n+1):
    check = False
    for j in range(1,i//2+1): 
        if(d[i-j]>(i-j) and d[j]>j): 
            check = True
            break
    if(check == False): cnt+=i 

print(cnt)