res = 0

n = 1000000

for i in range(1,n):
    s = ""
    t = ""

    d=i
    while(d):
        s+=chr(ord('0')+d%2)
        d//=2

    d=i
    while(d):
        t+=chr(ord('0')+d%10)
        d//=10

    if(s==s[::-1] and t==t[::-1]): res+=i

print(res)