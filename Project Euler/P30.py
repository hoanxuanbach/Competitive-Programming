n = 1000000

s = 0 

for i in range(10,n):
    d = i 
    x = 0
    while(d):
        k = d%10
        d//=10
        x+=pow(k,5)
    if(x==i): s+=i

print(s)