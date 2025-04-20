
#include "advisor.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn = 100005;
#define pii pair<int,int>
#define fi first
#define se second
int lst[maxn],nxt[maxn];

void ComputeAdvice(int *C, int N, int K, int M) {
    for(int i=0;i<N;i++) lst[i]=N;
    for(int i=N-1;i>=0;i--){
        nxt[i]=lst[C[i]];
        lst[C[i]]=i;
    }
    set<pii> s;
    for(int i=0;i<K;i++) s.insert({lst[i],i});
    vector<int> c(N+1,0);
    for(int i=0;i<N;i++){
        if(s.find({i,C[i]})!=s.end()) c[i]=1,s.erase({i,C[i]});
        else s.erase(*s.rbegin());
        s.insert({nxt[i],C[i]});
    }
    for(int i=0;i<K;i++) WriteAdvice(c[lst[i]]);
    for(int i=0;i<N;i++) WriteAdvice(c[nxt[i]]);
}
