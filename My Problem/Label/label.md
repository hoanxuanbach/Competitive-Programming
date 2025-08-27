## Problem Statement


You are given an undirected graph with:
- $N$ vertices,
- $M$ edges (no multiple edges between a pair of vertices),
- and $K$ colors.

Each vertex must be assigned one of the $K$ colors (colors are numbered $1$ to $K$) such that:

- For **every vertex $u$**, there exists a connected subgraph that is a tree of exactly $K$ vertices containing $u$,  
  and the $K$ vertices in that tree use **all $K$ different colors**.

Your task is to find **one valid coloring** of the vertices.

### Input

A line containing three integers $N, M, K$ — the number of vertices, the number of edges, and the number of colors. $(2 \le N, M \le 2 \times 10^5)$,$(2\le K \le N)$, $(4 \le N \times K \le 4 \times 10^5)$.

Then $M$ lines follow, each containing two integers $u, v$ $(1 \le u, v \le N)$, representing an edge between vertices $u$ and $v$.  

No multiple edges between the same pair of vertices.

### Output

If no valid coloring exists, print `-1`.

Otherwise:
1. Print one line containing $N$ integers $a_1, a_2, \dots, a_N$ $(1 \le a_i \le K)$,  
   where $a_i$ is the color of vertex $i$.
2. Then print $N$ more lines.  
   For each vertex $i$ $(1 \le i \le N)$, print $K-1$ integers — the indices of the edges (from input, indexed $1 \dots M$) forming a spanning tree of size $K$ that includes vertex $i$ and contains all $K$ colors.  
   The order of edges in a line can be arbitrary.

### Example

**Input**

4 3 2

1 2

1 3

1 4

**Output**

1 2 2 2 

1 

1 

2 

3 
