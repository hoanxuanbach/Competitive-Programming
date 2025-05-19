## Problem Statement

You are given an array $a$ consisting of $n$ integers.

An array is called **beautiful** if every distinct value in the array appears the same number of times.

For example:
- $[1, 1]$ is a beautiful array because it contains only the value $1$.
- $[1, 2, 1, 2]$ is a beautiful array because both values $1$ and $2$ appear $2$ times.
- $[1, 2, 1, 2, 3]$ is **not** a beautiful array because the value $3$ appears only once, while $1$ and $2$ each appear twice.

Your task is to calculate how many **non-empty subarrays** of array $a$ are beautiful.

---

### Input

The first line contains a single integer $n$ $(1 \leq n \leq 2*10^5)$ — the size of the array.

The second line contains $n$ integers $a_1, a_2, \dots, a_n$ $(1 \leq a_i \leq 2*10^5)$ — the elements of the array.

---

### Output

Print a single integer — the number of non-empty beautiful subarrays of $a$.

---

### Example

**Input**

5

1 2 1 2 3

**Output**

11