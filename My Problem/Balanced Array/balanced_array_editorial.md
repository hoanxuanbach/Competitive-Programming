# Editorial

## Definition

$S(l,r)$ : the set of different elements from $l$ to $r$

$cnt(l,r,x)$ : the number of occurrences of $x$ from $l$ to $r$

$mx(l,r) : max(cnt(l,r,x)) \forall 1 \leq x \leq 2\times10^5$

$A(l,r) : \{x | x \in S(l,r), cnt(l,r,x) = mx(l,r) \}$

$B(l,r) : S(l,r) \setminus A(l,r)$

$pos(l,r,x)$ : the minimum $i$ that $l \leq i \leq r$ and $a_i = x$ 

## Solution

We use **Divide and Conquer** algorithm. 

That is, in function $dnc(l,r)$, we calculate the number of subarrays $(x,y)$ that $(l \leq x \leq mid < y \leq r)$ with $mid = \left \lfloor \dfrac{l+r}{2} \right \rfloor$ and then call $dnc(l,mid)$ and $dnc(mid+1,r)$

There are 3 cases:

### Case 1: $S(x,mid) = S(mid+1,y)$

We have $S(x,mid) = \{s_1,s_2,...,s_m\}$ with $m = |S(x,mid)|$

$(x,y)$ is a beautiful subarray if:

$cnt(x,y,s_1) = cnt(x,y,s_2) = ... = cnt(x,y,s_m)$

$cnt(x,mid,s_1) + cnt(mid+1,y,s_1) = ... = cnt(x,mid,s_m) + cnt(mid+1,y,s_m)$

$\{cnt(x,mid,s_2) - cnt(x,mid,s_1),...,cnt(x,mid,s_m)-cnt(x,mid,s_{m-1})\} = \{cnt(mid+1,y,s_1) - cnt(mid+1,y,s_2),...,cnt(mid+1,y,s_{m-1})-cnt(mid+1,y,s_m)\}$

Finally, we use hashing of $S(x,mid)$ and $\{cnt(x,mid,s_2) - cnt(x,mid,s_1),...,cnt(x,mid,s_m)-cnt(x,mid,s_{m-1})\}$ to count the number of matched $y$. 

### Case 2: $S(x,mid) \subset S(mid+1,y)$ or $S(mid+1,y) \subset S(x,mid)$ 

WLOG, we handle the case $S(mid+1,y) \subset S(x,mid)$

We have $mx(x,mid)=mx(x,y)$ and $B(x,mid) = S(mid+1,y)$. 

Because we know that $S(x,mid) = S(x,y)$ so if we have $x$ we can see that $y = x+mx(x,mid)*|S(x,mid)| - 1$. To check whether $(x,y)$ is a beautiful subarray, we also use hashing.

### Case 3: $S(x,mid) \not\subset S(mid+1,y)$ and $S(mid+1,y) \not\subset S(x,mid)$ 

We have these conditions:

$B(x,mid) = B(mid+1,y)$

$A(x,mid) \cap A(mid+1,y) = \varnothing$

$mx(x,mid) = mx(mid+1,y)$

If $B(x,mid) = \{s_1,s_2,...,s_m\}$ with $m = |B(x,mid)|$, $cnt(x,mid,s_i)+cnt(mid+1,y,s_i) = mx(x,mid) \forall 1 \leq i \leq m$

For each $x$, we can see that $y < pos(mid+1,r,k) \forall k \in A(x,mid)$ to satisfy the condition $A(x,mid) \cap A(mid+1,y) = \varnothing$

To count the number of matched $y$ we use sweep line and hashing. 







