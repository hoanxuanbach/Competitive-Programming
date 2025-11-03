import random

def roll():
    a, b = random.randint(1, 4), random.randint(1, 4)
    return a + b, a == b

def next_r(pos):
    for r in [5, 15, 25, 35]:
        if pos < r: return r
    return 5

def next_u(pos):
    for u in [12, 28]:
        if pos < u: return u
    return 12

CC = [0, 10] + [None]*14
CH = [0, 10, 11, 24, 39, 5, "R", "R", "U", -3] + [None]*6
random.shuffle(CC)
random.shuffle(CH)

pos = 0 
cnt = [0]*40
double = 0 

names = [
    "GO", "A1", "CC1", "A2", "T1", "R1", "B1", "CH1", "B2", "B3",
    "JAIL", "C1", "U1", "C2", "C3", "R2", "D1", "CC2", "D2", "D3",
    "FP", "E1", "CH2", "E2", "E3", "R3", "F1", "F2", "U2", "F3",
    "G2J", "G1", "G2", "CC3", "G3", "R4", "CH3", "H1", "T2", "H2"
]


for _ in range(10000000):
    s,dbl = roll()
    if(dbl): double+=1
    else: double=0
    if(double==3):
        pos=10
        double=0
    else:
        pos=(pos+s)%40
        name=names[pos]
        if(name=="G2J"):
            pos=10
        elif(name[0]=='C' and name[1]=='C'):
            card = CC[0]
            CC = CC[1:]+[card]
            if(card==0): pos=0
            elif(card==10): pos=10
        elif(name[0]=='C' and name[1]=='H'):
            card = CH[0]
            CH = CH[1:]+[card]
            if(card=='R'): pos=next_r(pos)
            elif(card=='U'): pos=next_u(pos)
            elif(card==-3):
                pos=(pos+37)%40
                if(names[pos][0]=='C' and names[pos][1]=='C'):
                    card=CC[0]
                    CC=CC[1:]+[card]
                    if(card==0): pos = 0
                    elif(card==10): pos = 10
            elif(card!=None):
                pos=card
    
    cnt[pos]+=1

X=0
Y=0
Z=0 
for i in range(1,40):
    if(cnt[i]>cnt[X]): 
        Z=Y
        Y=X
        X=i
    elif(cnt[i]>cnt[Y]): 
        Z=Y
        Y=i
    elif(cnt[i]>cnt[Z]): 
        Z=i

print(X,Y,Z)