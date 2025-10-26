
n = 1
for i in range(1,101): 
    n*=i

print(n)

digit=0
while(n):
    digit+=n%10
    n//=10

print(digit)
