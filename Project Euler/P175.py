a, b = 123456789, 987654321
S = []

while a and b:
    if(b>=a):
        S.append((b//a,1))
        b%=a
    else:
        S.append((a//b,0))
        a%=b

if S[-1][1] == 0:
    x,y = S[-1]
    S.pop()
    if x>1:
        S.append((x-1,0))
    S.append((1,1))

S = S[::-1]

res = ""
for x,y in S:
    print(x)
    res+=str(x)
    res+=','

print(res)