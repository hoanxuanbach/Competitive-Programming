n = pow(7,17)

x = 1

T = 0
while(2*x-1<=n):
    T+=2*x-1
    d=(n-(2*x-1))//(2*x)
    T+=2*d*x
    x*=2

print(T)