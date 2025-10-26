n = 100

m = {}

for a in range(2,n+1): 
    for b in range(2,n+1): m[pow(a,b)]=1

print(len(m))