## Problem Statement

You are given an array $a$ of $n$ integers.

We define a **beautiful sequence** as a sequence in which all elements are equal.

Let $cost(x)$ be the minimum number of operations needed to convert sequence $x$ into a beautiful sequence. You are allowed to perform the following two operations:

1. $x_i = \dfrac{x_i}{p^k}$, where $p$ is a prime number and $x_i$ is divisible by $p^k$.
2. $x_i = x_i \times p^k$, where $p$ is a prime number.

Your task is to compute the sum of $cost(x)$ over all $2^n$ **subsequences** of array $a$, modulo $998244353$.

---

### Definitions

- A **subsequence** $S$ of array $a$ is a sequence that can be obtained by deleting zero or more elements (not necessarily contiguous) from $a$.
- A **beautiful sequence** is one where all elements are equal.
- Each operation (either multiplication or division by a prime power) counts as one step.

---

### Input

- The first line contains a single integer $n$ $(1 \leq n \leq 10^6)$ — the number of elements in the array.
- The second line contains $n$ integers $a_1, a_2, \dots, a_n$ $(1 \leq a_i \leq 10^6)$ — the elements of the array.

---

### Output

Output a single integer — the sum of $cost(x)$ for all $2^n$ subsequences of $a$, modulo $998244353$.

### Example

**Input**

4

1 6 2 3

**Output**

20
