
def f(x):
    for i in range(2,x+1):
        if(i*i>x): break
        if(x%i==0): return 0
    return 1


n = 29999
x = 1 

k = 0
cnt = 1

for i in range(2,n,2):
    for j in range(4):
        x+=i
        cnt+=1
        k+=f(x)
    
    if(k*10<cnt):
        print(i+1)
        break

print(k,cnt)