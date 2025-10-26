n = 100000000

while(n):
    x = n*n
    s = str(x)
    c = True
    for i in range(9):
        if(s[2*i]!=chr(ord('0')+i+1)):
            c = False
            break
    
    if(c): break
    else: n+=1

print(n*10)