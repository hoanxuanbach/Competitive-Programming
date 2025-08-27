## Problem Statement

You are given two integers $n, k$ such that $k \leq n$.  

A sequence of integers $a_1, a_2, \ldots, a_n$ is called a **beautiful sequence** if:

- $1 \leq a_i \leq k$ for all $1 \leq i \leq n$ 
- For every position $1 \leq i \leq n$, there exists an index $1 \leq j \leq n-k+1$ such that $j \leq i < j+k$ and sequence $a_j, a_{j+1}, \ldots, a_{j+k-1}$ is a **permutation** of the numbers from $1 \to k$.

Your task is to count how many such beautiful sequences exist.  
Output the answer **modulo** $998244353$.

### Input

The first line contains two integers $n, k$  $(1 \leq k \leq n \leq 2 \times 10^5)$

### Output

Print a single integer — the number of beautiful sequences modulo $998244353$.

### Subtasks

- **Subtask 1 (10%)**: $2k \geq n$  
- **Subtask 2 (20%)**: $n \leq 500$  
- **Subtask 3 (30%)**: $n \leq 5000$  
- **Subtask 4 (40%)**: No additional constraints  

### Example

**Input**

6 3

**Output**

36
