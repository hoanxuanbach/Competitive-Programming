## Problem Statement

You are given a sequence of $n$ numbers $a_1, a_2, \ldots, a_n$.  
We will perform $q$ operations of two possible types:

- **Operation 1**: Randomly shuffle the numbers in the segment $[l, r]$.  
- **Operation 2**: Compute the expected value of the sum of numbers in the segment $[l, r]$ modulo $998244353$.  

Let $M = 998244353$. It can be proven that the answer can be expressed as an irreducible fraction $\frac{p}{q}$, where $p$ and $q$ are integers and $q \not\equiv 0 \pmod{M}$.  

You must output an integer equal to $p \cdot q^{-1} \bmod M$.  
In other words, output an integer $x$ such that:

- $0 \le x < M$  
- $x \cdot q \equiv p \pmod{M}$


### Input


- The first line contains an integer $n$  $(1 \leq n \leq 5 \times 10^5)$  

- The second line contains $n$ integers $a_1, a_2, \ldots, a_n$  $(0 \leq a_i < 998244353)$  

- The third line contains an integer $q$  $(1 \leq q \leq 5 \times 10^5)$  

- Each of the next $q$ lines contains three integers $id, l, r$ where $id = 1$ or $id = 2$ indicates the operation type  $(1 \leq l \leq r \leq n)$  

### Output

For each operation of type 2, print the corresponding answer.

### Subtasks

- **Subtask 1 (10%)**: $n \leq 5000$, number of type 1 operations $\leq 10$, and for type 1 operations $(r-l \leq 1)$.  
- **Subtask 2 (20%)**: $n \leq 6, q \leq 10^5$  
- **Subtask 3 (30%)**: $n, q \leq 5000$  
- **Subtask 4 (40%)**: No additional constraints  

### Example

**Input**

	
5

1 2 3 4 5

5

2 1 3

1 1 2

2 2 5

1 2 3

2 1 2

**Output**

6

499122190

249561092
