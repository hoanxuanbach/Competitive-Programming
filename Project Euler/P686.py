from decimal import Decimal, getcontext

s = 123

getcontext().prec = 50
x = Decimal(s).ln()/Decimal(2).ln()
y = Decimal(s+1).ln()/Decimal(2).ln()
d = Decimal(10).ln()/Decimal(2).ln()

k = 0
cnt = 678910

while(cnt):
    x+=d
    y+=d
    if(int(x)<int(y)):
        cnt-=1
        k=int(y)

print(k)
    



