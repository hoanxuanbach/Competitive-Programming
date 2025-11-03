import math

N = int(input())
cnt = 0

for D in range(1,N+1):
    x = int(math.sqrt(D))
    if(x*x==D):
        continue
    
    m = 0
    d = 1
    a = x

    period = []
    seen = {}
    while True:
        m = d*a-m
        d = (D-m*m)//d 
        a = (x+m)//d 

        if((m,d) in seen):
            break
        
        seen[(m,d)] = True
        period.append(a)
    
    if(len(period)%2==1):
        cnt+=1

print(cnt)