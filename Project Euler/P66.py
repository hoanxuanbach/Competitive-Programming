import math

N = int(input())

X = 0 
Y = -1

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
    
    k = len(period)
    if(k%2==1):
        period *= 2
    period.pop()

    #print(D,period)
    
    A = 0 
    B = 1
    k = len(period)
    for i in range(k-1,-1,-1):
        A+=period[i]*B
        A,B=B,A
    
    A+=x*B
    if(A>X):
        X,Y=A,D

print(X,Y)