## Problem Statement

Bách challenged Dương with the following problem:

You are given a sequence of integers:

$$
c_1, c_2, \ldots, c_{2k}
$$

Dương wants to create as many **balanced parenthesis strings** of length $2k$ as possible such that:

- Let $b_i$ = the number of such strings that contain the character `(` at position $i$.
- For every $1 \le i \le 2k$, the condition holds:

$$
\sum_{j=1}^{i} b_j \le \sum_{j=1}^{i} c_j
$$

Bách wants to know the **maximum number of balanced parenthesis strings** that Dương can create.

Since Dương found the problem too easy, he added a twist:

You are given a sequence:

$$
a_1, a_2, \ldots, a_n
$$

- There are $q$ queries, each of the form $(l, r)$.
- For each query:
  - Let $r - l + 1 = 2k$.
  - Define $c_i = a_{l+i-1}$.
  - Solve the original problem on this subsequence.

Your task is to output the answer for each query.

---

### Input

- The first line contains an integer $n$  $(1 \leq n \leq 2 \times 10^5)$

- The second line contains the sequence:  $a_1, a_2, \ldots, a_n$
  $(0 \leq a_i \leq 2 \times 10^5)$

- The third line contains an integer $q$  $(1 \leq q \leq 2 \times 10^5)$

- Each of the next $q$ lines contains two integers $(l, r)$ with:  $(1 \le l \le r \le n), (r - l + 1) \text{ is even}$

---

### Output

- Print $q$ lines.  
- The $i$-th line contains the answer to the $i$-th query.

---

### Subtasks
- **Subtask 1 (10%)**: $n, q \le 5000$ and $a_i \le 1$ 
- **Subtask 2 (20%)**: $a_i \le 1$ 
- **Subtask 3 (30%)**: $n, q \le 5000$  
- **Subtask 4 (40%)**: No additional constraints

### Example

**Input**

5

6 2 4 3 5

2

1 4

2 5

**Output**

6

2
