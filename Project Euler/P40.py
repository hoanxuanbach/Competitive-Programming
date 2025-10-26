
n = 1
m = 1000000
s = ""

while(len(s)<m):
    d = n
    t = ""
    while(d):
        t+=chr(ord('0')+d%10)
        d//=10

    t=t[::-1]
    s+=t
    n+=1

x=1
res=1
while(x<=m):
    res*=(ord(s[x-1])-ord('0'))
    x*=10

print(res)
