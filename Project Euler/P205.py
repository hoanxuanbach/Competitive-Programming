from decimal import Decimal, getcontext
getcontext().prec = 10



pA = Decimal(1)/Decimal(4)
pB = Decimal(1)/Decimal(6)
S = 36

A = [Decimal(0)]*(S+1)
B = [Decimal(0)]*(S+1)

A[0]=B[0]=1

for _ in range(9):
    for i in range(S,-1,-1):
        A[i]=0
        for j in range(1,min(i,4)+1):
            A[i]+=A[i-j]*pA

for _ in range(6):
    for i in range(S,-1,-1):
        B[i]=0
        for j in range(1,min(i,6)+1):
            B[i]+=B[i-j]*pB

res = 0

for i in range(0,S+1): 
    for j in range(i):
        res+=A[i]*B[j]

print(res)