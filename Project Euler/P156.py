
def f(n,d):
    cnt = 0
    s = n
    x = 1
    while n :
        k=n%10
        if k>d :
            cnt+=x
        elif k == d:
            cnt+=s-n*x+1
        n//=10
        cnt+=n*x
        x*=10

    return cnt

N = 12

pw = [1]
for i in range(N):
    pw.append(pw[-1]*10)

res = 0

for d in range(1,10):
    x = 1   
    k = 0 
    while x <= pw[-2] :
        w = abs(f(x,d)-x)
        if w == 0:
            res+=x
            x+=1
        else:
            x+=(w+k)//(k+1)
            if x >= pw[k+1]:
                k+=1
                x=pw[k]

print(res)