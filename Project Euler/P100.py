import math

a = 1 
b = 1

for i in range(1,100):
    a,b = a+2*b,a+b 
    if(i%2==0):
        x = (a+1)//2
        s = x*x+(x-1)*(x-1)
        S = int(math.sqrt(s))

        if(S*S==s):
            print(x,(S+1)//2)

