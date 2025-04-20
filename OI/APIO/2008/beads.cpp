#include "beads.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn = 300005;

int N,M,P[maxn];
vector<pair<int,int>> pos[maxn];

void init(int _N, int _M, std::vector<int> A) {
    N=_N;M=_M;
    for(int i=1;i<=N;i++) pos[i].push_back({0,i}),P[i]=i;
    for(int i=0;i<M;i++){
        int x=A[i],y=A[i]+1;
        swap(P[x],P[y]);
        pos[P[x]].push_back({i+1,x});
        pos[P[y]].push_back({i+1,y});
    }
}

int ask(int K, int J) {
    int p=upper_bound(pos[K].begin(),pos[K].end(),make_pair(J,N))-pos[K].begin()-1;
    return pos[K][p].second;
}
