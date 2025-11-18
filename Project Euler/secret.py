from PIL import Image
import numpy as np

# Load and convert to grayscale
img = Image.open("secret.png").convert("L")

# Convert to numpy array (2D)
A = np.array(img)

n,m = A.shape
#print(n,m)

for i in range(n):
    for j in range(m):
        A[i][j]%=7

D = 1
N = 10**12

while N:
    print(N,flush = True)
    k = N%7
    for _ in range(k):
        B = np.zeros((n, m), dtype=int)
        for i in range(n):
            for j in range(m):
                x=(i+D)%n 
                B[i][j]+=A[x][j]
                x=(i+n-D%n)%n 
                B[i][j]+=A[x][j]
                x=(j+D)%m
                B[i][j]+=A[i][x]
                x=(j+m-D%m)%m
                B[i][j]+=A[i][x]

                B[i][j]%=7

        A = B

    N//=7
    D*=7

for i in range(n):
    for j in range(m):
        A[i][j]=(255/6)*A[i][j]

img = Image.fromarray(A)
img.show()       
img.save("euler.png")