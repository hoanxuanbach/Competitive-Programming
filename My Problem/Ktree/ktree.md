## Problem Statement

You are given a tree with $n$ vertices, rooted at vertex $1$. Each vertex $i$ is initially colored $c_i \in \{0, 1\}$. Each edge $i$ has a weight $w_i$.

You will receive $q$ queries, each belonging to one of the following two types:

- **Type 1:**  
  `1 u` — Flip the color of vertex $u$ (i.e., change $c_u$ from $0$ to $1$ or from $1$ to $0$).

- **Type 2:**  
  `2 u v t k` — Consider all vertices $x$ in the subtree rooted at $u$ such that $c_x = t$.  
  Among all paths from $v$ to such vertices $x$, output the **lengths of the $k$ longest paths**.  
  (It is guaranteed that there are at least $k$ such vertices in the subtree of $u$ with color $t$.)

A vertex $x$ is in the subtree of $u$ if $u$ lies on the path from the root (vertex $1$) to $x$.

---

### Input

- The first line contains two integers $n$ and $q$ $(1 \leq n, q \leq 10^5)$ — the number of vertices and the number of queries.
- The second line contains $n$ integers $c_1, c_2, \dots, c_n$ $(c_i \in \{0,1\})$ — the initial colors of the vertices.
- The next $n-1$ lines each contain three integers $u_i$, $v_i$, $w_i$ $(1 \leq u_i, v_i \leq n, -10^9 \leq w_i \leq 10^9)$ — describing an undirected edge between vertices $u_i$ and $v_i$ with weight $w_i$.
- The next $q$ lines each describe a query, either of:
  - `1 u` — flip color of vertex $u`
  - `2 u v t k` — as described above

---

### Output

For each query of type 2, output a single line containing $k$ integers — the lengths of the $k$ longest paths from $v$ to valid vertices $x$, in **descending order**.

---

### Subtasks

- **Subtask 1 (20%)**: $n \leq 10^4$
- **Subtask 2 (15%)**: In all queries of type 2, $u = v$
- **Subtask 3 (25%)**: All edge weights satisfy $w_i \geq 0$
- **Subtask 4 (40%)**: No additional constraints

### Notes

- The tree is rooted at vertex $1$.
- Flipping a color means changing it from `0` to `1`, or from `1` to `0`.
- You may assume that the number of valid vertices in each type 2 query is at least $k`, so the answer always exists.

