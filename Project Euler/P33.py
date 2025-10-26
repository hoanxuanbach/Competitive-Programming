import math

x = 1
y = 1

for i in range(10,100):
    for j in range(i+1,100):
        a=i//10
        b=i%10
        c=j//10
        d=j%10

        if(a==d and i*c==j*b):
            x*=i
            y*=j

        if(b==c and i*d==j*a):
            x*=i
            y*=j

g=math.gcd(x,y)
print(x//g,y//g)