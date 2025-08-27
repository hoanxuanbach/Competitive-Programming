## Problem Statement


Count the number of permutations $p$ with $N$ elements from $1$ to $N$ that satisfy the following conditions:

- **Problem 1**: $p_{p_i} = i \ \forall \ i$  
- **Problem 2**: $p_{p_i} \ne i \ \forall \ i$

### Input

The first line contains a single integer $N$  $(1 \le N \le 10^6)$

### Output

Print two integers separated by a space:  
  - The answer to **Problem 1**  
  - The answer to **Problem 2**  

Both answers must be given modulo $10^9 + 7$.

### Example

**Input**

7

**Output**

232 1140
