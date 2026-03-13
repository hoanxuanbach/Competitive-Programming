import mpmath as mp

def cal(n,lim):
    n = mp.mpf(n)
    res = mp.mpf('0')
    for k in range(1,lim+1):
        s = 1+mp.lambertw(-mp.e**-1,k)
        res += 2*mp.re(mp.e**(s*n)/s)    
    return res

mp.mp.dps = 100
n = int(input())
lim = int(input())
D = cal(n,lim)
M = int(mp.ceil(-mp.log10(mp.fabs(D))))

for i in range(1,10):
    if(M): 
        M-=1

X = D*mp.power(10,M)+mp.mpf(2)/3
K = X-mp.floor(X)
T = 8
S = ""

while(len(S)<T):
    K*=10
    d=int(mp.floor(K))
    K-=d

    if(d!=6):
        S+=chr(ord('0')+d)

print(S)



