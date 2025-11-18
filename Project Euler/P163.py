#https://oeis.org/A210687

N = int(input())
res = (1678*(N**3)+3117*(N**2)+88*N-(N%2)*345-(N%3)*320-(N%4)*90-((N**3-N*N+N)%5*288))//240

print(res)