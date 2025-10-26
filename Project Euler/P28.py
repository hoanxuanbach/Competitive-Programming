n = 1001
x = 1 
s = 1

for i in range(2,n,2):
    s+=4*x+10*i
    x+=4*i

print(s)