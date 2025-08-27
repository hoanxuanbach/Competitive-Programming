## Problem Statement

You are given a string of length $N$. For each integer $d \in \{0, 1, 2, \dots, K\}$, we delete exactly $d$ characters from the string (keeping the order of the remaining characters).  

Your task is to compute how many **distinct subsequences** can be obtained for each $d$.

### Input

The first line contains two integers $N, K$ $(1 \le K \le N \le 2 \times 10^5,\ 1 \le N \times K \le 10^6)$
  
The second line contains a string of length $N$, which only include **lowercase letters**.

### Output

A single line containing $K + 1$ integers: the number of distinct subsequences obtained by deleting exactly $0, 1, 2, \dots, K$ characters from the original string.  

All answers must be printed **modulo $10^9 + 7$**.

### Example

**Input**

10 10

Succulento

**Output**

1 9 37 91 148 167 134 77 31 8 1
