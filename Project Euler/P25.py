
n = 2

A = 1
B = 1

L = pow(10,999)
while(B<L):
    n+=1
    A,B=B,A
    B+=A

print(n)