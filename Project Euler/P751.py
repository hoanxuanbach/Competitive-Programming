
x = 2 
s = "2."

for i in range(1,24):
    b = x
    for j in range(i):
        b = int(b)*(b-int(b)+1)

    b = int(b)

    s+=str(b)
    x=float(s)

print(f"{x:.24f}")
print(s)

