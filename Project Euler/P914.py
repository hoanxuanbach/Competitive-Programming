import math

R = 10**18
val = 0
c = 2*R
a = R*math.sqrt(2)
X = int(math.sqrt((c+a)/2))
Y = int(math.sqrt((c-a)/2))
D = 1000

for x in range(X-D,X+D):
    for y in range(Y-D,Y+D):
        if((x%2==1 and y%2==1) or math.gcd(x,y)!=1):
            continue
        if(x*x+y*y>=2*R):
            continue
        val=max(val,(x-y)*y)

print(val)