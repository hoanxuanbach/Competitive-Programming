from decimal import Decimal, getcontext
getcontext().prec = 10

lst = []

with open("input.txt", "r") as f:
    for line in f:
        values = [int(x) for x in line.strip().split(',')]
        lst.append(values)

id = -1
mx = 0

for i in range(len(lst)):
    a = lst[i][0]
    b = lst[i][1]

    f = Decimal(a).ln()*b
    if(f>mx):
        mx=f
        id=i

print(id+1)