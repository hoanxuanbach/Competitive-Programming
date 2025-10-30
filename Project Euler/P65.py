
a = 0 
b = 1

n = int(input())
X = [2,1,2]
for i in range(3,n):
    if(i%3!=2):
        X.append(1)
    else:
        X.append(2*(i+1)//3)

X.reverse()


a = X[0]
for i in range(1,len(X)):
    a,b=b,a
    a+=X[i]*b

print(a,b)

S = 0 
while(a):
    S+=(a%10)
    a//=10

print(S)