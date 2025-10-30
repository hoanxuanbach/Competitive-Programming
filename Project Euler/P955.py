
n = 70
id = 0
a = 2

for i in range(n-1):
    x=a*(a+1)

    p = -1
    q = -1

    m = a
    d1 = []
    for d in range(1,m):
        if(d*d>m):
            break
        if(m%d==0):
            d1.append(d)
            if(d*d!=m): d1.append(m//d)
    
    m = a+1
    d2 = []
    for d in range(1,m):
        if(d*d>m):
            break
        if(m%d==0):
            d2.append(d)
            if(d*d!=m): d2.append(m//d)

    for dx in d1:
        for dy in d2:
            d = dx*dy
            if(d*d>x): continue

            k = x//d
            if((d%2)==(k%2)):
                continue

            k-=1
            if(k<d):
                continue

            b=(k-d)//2
            c=(k+d)//2

            if(c>a):
                if(p==-1 or b<p):
                    p=b
                    q=c

        
    
    id+=p
    a=q

    print(i,id,a,flush=True)

print(id)
