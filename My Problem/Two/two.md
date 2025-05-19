## Problem Statement

You are given a $2 \times n$ grid. The rows are numbered from $0$ to $1$ (top to bottom), and the columns are numbered from $1$ to $n$ (left to right).

Each cell of the grid contains a unique number from $1$ to $2n$, with every number appearing exactly once.

You are given $q$ queries. In each query, you are allowed to only step through cells whose values lie in a given range $[L, R]$, and must determine whether it is possible to move from cell $(x_1, y_1)$ to cell $(x_2, y_2)$ by stepping only through such cells. Movement is allowed to **adjacent cells** (sharing a side), i.e., up, down, left, or right.

---

### Input

- The first line contains a single integer $n$ $(1 \leq n \leq 2 \cdot 10^5)$ — the number of columns in the grid.
- The second line contains $n$ integers — the values in row $0$ (top row), from left to right.
- The third line contains $n$ integers — the values in row $1$ (bottom row), from left to right.
- The fourth line contains a single integer $q$ $(1 \leq q \leq 2 \cdot 10^5)$ — the number of queries.
- The next $q$ lines each contain six integers:  
  $x_1$, $y_1$, $x_2$, $y_2$, $L$, $R$  
  $(0 \leq x_1, x_2 \leq 1, 1 \leq y_1 \leq y_2 \leq n, 1 \leq L \leq R \leq 2n)$ — describing a query asking whether it is possible to travel from $(x_1, y_1)$ to $(x_2, y_2)$ using only values in range $[L, R]$.

---

### Output

For each query, output `YES` if it is possible to go from the start to the end cell using only allowed values, otherwise output `NO`.

---

### Notes

- Cells are indexed as $(x, y)$, where $x$ is the row (0 or 1) and $y$ is the column (from 1 to $n$).
- You can only move to adjacent cells: up, down, left, or right.
- You may not leave the $2 \times n$ grid.

### Example

**Input**

4

1 2 3 4

5 6 7 8

4

0 1 1 3 1 8

1 2 0 4 3 4

0 4 1 4 2 6

1 1 1 4 5 7

**Output**

YES

NO

NO

NO
