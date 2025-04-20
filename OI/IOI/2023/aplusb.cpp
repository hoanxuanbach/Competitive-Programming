#include "aplusb.h"
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second

std::vector<int> smallest_sums(int N, std::vector<int> A, std::vector<int> B) {
	vector<int> cur(N,0);
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    for(int i=0;i<N;i++) pq.push({A[i]+B[0],i});
    vector<int> res(N);
    for(int i=0;i<N;i++){
        auto [d,x]=pq.top();pq.pop();
        res[i]=d;cur[x]++;
        if(cur[x]<N) pq.push({A[x]+B[cur[x]],x});
    }
    return res;
}
