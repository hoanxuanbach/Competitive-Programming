from fractions import Fraction

N = 35

S = {Fraction(a,b) for b in range(1,N+1) for a in range(1,b)}

L = list(S)

T = {x*x : x for x in S}

ans = set()

m = len(L)
for i in range(m):
    for j in range(m):
        x,y = L[i],L[j]
        z = x+y
        if z in S:
            ans.add(x+y+z)
        
        z = x*x+y*y
        if z in T.keys():
            ans.add(x+y+T[z])

        z = 1/(1/x+1/y)
        if z in S:
            ans.add(x+y+z)
        
        z = 1/(1/(x*x)+1/(y*y))
        if z in T.keys():
            ans.add(x+y+T[z])

F = sum(ans)
print(F.numerator+F.denominator)