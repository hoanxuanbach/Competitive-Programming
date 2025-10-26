cnt=0
for i in range(1,10000):
    x = i
    check = False

    for t in range(51):
        s=str(x)
        if(t and s==s[::-1]):
            check = True
            break
        x+=int(s[::-1])

    if(check == False): cnt+=1

print(cnt)