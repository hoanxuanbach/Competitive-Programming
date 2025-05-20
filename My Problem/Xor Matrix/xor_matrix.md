## Problem Statement

You are given an $n$-dimensional grid, where each dimension has size $a_i$. Your task is to fill the grid with **distinct integers** such that for every pair of **adjacent** points filled with values $x$ and $y$, the condition $x \oplus y = 2^d$ holds for some integer $d$.

Two points $(i_1, i_2, \dots, i_n)$ and $(j_1, j_2, \dots, j_n)$ are considered **adjacent** if:

$$
|i_1 - j_1| + |i_2 - j_2| + \dots + |i_n - j_n| = 1
$$

Let $C$ be the **maximum number** placed in any of the grid's cells. Your goal is to **minimize $C$**, and output the **minimum possible value of $C$ in binary representation**.

---

### Input

- The first line contains an integer $n$ $(1 \leq n \leq 2 \times 10^5)$ — the number of dimensions.
- The second line contains $n$ integers $a_1, a_2, \dots, a_n$ $(1 \leq a_i \leq 13)$ — the size of each dimension.

---

### Output

Output a single line containing the smallest possible value of $C$ in **binary representation**.

### Example

**Input**

2

3 3

**Output**

1010
