
s = 1

for a in range(1,100):
    for b in range(1,100):
        x = pow(a,b)
        d = 0 
        while(x):
            d+=x%10
            x//=10
    
        s=max(s,d)

print(s)