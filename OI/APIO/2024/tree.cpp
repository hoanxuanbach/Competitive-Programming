#include "tree.h"
#include <bits/stdc++.h>
using namespace std;

std::vector<int> compute(int N, std::vector<int> F) {
	vector<int> d(N);
    for(int i=1;i<N;i++) d[F[i]]++;
    priority_queue<int> pq;
    vector<int> res;
    for(int i=0;i<N;i++) if(!d[i]) pq.push(i);
    while(pq.top()){
        int u=pq.top();pq.pop();
        res.push_back(u);
        d[F[u]]--;
        if(!d[F[u]]) pq.push(F[u]);
    }
    return res;
}
