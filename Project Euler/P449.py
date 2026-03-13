import mpmath as mp 
mp.mp.dps = 50

def surface_area(a):
    e = mp.sqrt(1-1/(a*a))
    return 2*mp.pi*a*a*(1+(1-e*e)/e*mp.atanh(e))

def mean_width(a):
    f = lambda t: mp.sin(t)*mp.sqrt(a*a*mp.sin(t)**2+mp.cos(t)**2)
    return mp.quad(f,[0,mp.pi])

a = int(input())
S = surface_area(a)
w = mean_width(a)

res = S+2*mp.pi*w+(4/3)*mp.pi
print(mp.nstr(res,12))