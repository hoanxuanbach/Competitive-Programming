#include "paint.h"
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second

int minimumInstructions(
    int N, int M, int K, std::vector<int> C,
    std::vector<int> A, std::vector<std::vector<int>> B) {

    vector<vector<int>> P(K);
    for(int i=0;i<M;i++) for(int x:B[i]) P[x].push_back(i);
    vector<int> d(M,0),pre;
    vector<bool> cc(N,false);
    for(int i=0;i<N;i++){
        int Max=0;
        vector<pii> nw;
        for(int x:P[C[i]]){
            int y=(x+M-1)%M;
            nw.push_back({x,d[y]+1});
        }
        for(int x:pre) d[x]=0;
        for(auto [x,val]:nw) d[x]=val,Max=max(Max,val);
        if(Max>=M) cc[i]=true;
        pre=P[C[i]];
    }
    deque<pii> dq;
    dq.push_back({-1,0});
    for(int i=0;i<N;i++){
        if(!cc[i]) continue;
        while(!dq.empty() && dq.front().fi<i-M) dq.pop_front();
        if(dq.empty()) continue;
        int val=dq.front().se+1;
        while(!dq.empty() && dq.back().se>=val) dq.pop_back();
        dq.push_back({i,val});
        if(i==N-1) return val;
    }
    return -1;
}
