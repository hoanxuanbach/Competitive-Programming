from fractions import Fraction

S = [4, 5, 6, 7, 8, 9, 10, 12, 12, 14, 15, 18, 20, 21, 24, 28, 30, 35, 36, 40, 42, 45, 56, 60, 63, 70, 72]

n = len(S)
res = 0

sum = Fraction(1,2)-Fraction(1,4)-Fraction(1,9)

A = S[:n//2]
B = S[n//2:]

mp = {}

n = len(A)

for i in range(1<<n):
    s = Fraction(0)
    for j in range(n):
        if i>>j&1 :
            s += Fraction(1,A[j]*A[j])
    
    if s <= sum :
        if(s not in mp.keys()): 
            mp[s] = 0
        
        mp[s] += 1

n = len(B)

for i in range(1<<n):
    s = Fraction(0)
    for j in range(n):
        if i>>j&1 :
            s += Fraction(1,B[j]*B[j])
    
    s = sum - s 
    if s in mp.keys():
        res+=mp[s]

print(res)


