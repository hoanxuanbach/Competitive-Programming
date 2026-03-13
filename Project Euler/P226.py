from math import sin,asin

def f(x):
    S = 0 
    for i in range(60):
        S+=abs(x*(1<<i)-round(x*(1<<i)))/(1<<i)
    return S

def g(x):
    return 0.5 - (x/2-x*x)**0.5

def h(x):
    if(x < 1e-13):
        return 0
    
    if(x <= 0.5):
        return h(2*x)/4+x*x/2
    else:
        return 0.5-h(1-x)

l,r = 0,0.5
for _ in range(100):
    m = (l+r)/2
    if(f(m)>g(m)):
        r=m
    else:
        l=m

ax,bx = l,0.5
ay,by = g(ax),g(bx)

R = 0.25
d = ((ax-bx)**2+(ay-by)**2)**0.5
angle = 2*asin(d/(2*R))
area = R*R/2*(angle-sin(angle))
area = (ay+by)*(bx-ax)/2-area
res = h(bx)-h(ax)-area
print("{:.8f}".format(res))