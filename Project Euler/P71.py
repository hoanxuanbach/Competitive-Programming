
N = 1000000

a = 0
b = 1

for d in range(N+1):
    n = (3*d-1)//7
    if(a*d<n*b): 
        a=n
        b=d

print(a,b)