

def g(ax,ay,bx,by,cx,cy):
    area=ax*by-ay*bx+bx*cy-by*cx+cx*ay-cy*ax
    return abs(area)

cnt = 0

with open("102.txt", "r") as f:
    for line in f:
        S = [int(x) for x in line.strip().split(",")]
        T = g(S[0],S[1],S[2],S[3],S[4],S[5])
        A = g(S[0],S[1],S[2],S[3],0,0)
        B = g(S[0],S[1],0,0,S[4],S[5])
        C = g(0,0,S[2],S[3],S[4],S[5])

        if(T==A+B+C):
            cnt+=1
    

print(cnt)