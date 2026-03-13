B = 14

def digit(X):
    d = 0
    while(X>0):
        d+=1
        X//=B
    return d

def transform(T):
    
    S = ""
    while(T>0):
        k = T%B
        T //=B
        if(k<10):
            S+=chr(ord('0')+k)
        else:
            S+=chr(ord('a')+k-10)

    return S

M = int(input())

D = B
T = 7 

while(digit(T)<M):
    D=D*D
    T=(2*T*T*T-3*T*T)%D
    T=(D-T)%D

S = transform(T)


if(len(S)>M):
    S=S[:M]

X = 0
D = 1
for i in range(M):
    k = 0
    if(S[i]>='0' and S[i]<='9'):
        k = ord(S[i])-ord('0')
    else:
        k = 10+ord(S[i])-ord('a')
    
    X+=D*k
    D*=B

Y = D+1-X
X = transform(X)
Y = transform(Y)

#print(X)
#print(Y)

res = 1
sX = 0 
sY = 0
for i in range(M):
    dX = 0
    if(X[i]>='0' and X[i]<='9'):
        dX = ord(X[i])-ord('0')
    else:
        dX = 10+ord(X[i])-ord('a')

    dY = 0
    if(Y[i]>='0' and Y[i]<='9'):
        dY = ord(Y[i])-ord('0')
    else:
        dY = 10+ord(Y[i])-ord('a')

    sX+=dX
    sY+=dY
    if(dX):
        res+=sX
    if(dY):
        res+=sY

res = transform(res)
res = res[::-1]

print(res)