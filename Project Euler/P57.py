
x = 0
y = 1
cnt = 0

for i in range(1000):
    x+=2*y
    x,y=y,x
    cnt+=len(str(x+y))>len(str(y))

print(cnt)
