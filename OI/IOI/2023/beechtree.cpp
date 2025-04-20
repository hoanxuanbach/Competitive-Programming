#include "beechtree.h"
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second
const int maxn = 2e5+5;

std::vector<int> beechtree(int N, int M, std::vector<int> P, std::vector<int> C)
{
    vector<int> res(N,1),sz(N,1);
    vector<set<pii>> s(N);
    vector<map<int,int>> c(N);
    auto check = [&](int u,int v){
        for(auto [d,x]:c[u]){
            if(c[v].find(d)==c[v].end() || sz[x]>sz[c[v][d]]) return 0;
        }
        return 1;
    };
    auto add = [&](int u,int v){
        auto it=s[u].insert({sz[v],v}).fi;
        int ok=1;
        if(it!=s[u].begin()) ok&=check(prev(it)->se,v);
        if(next(it)!=s[u].end()) ok&=check(v,next(it)->se);
        return ok;
    };
    auto cal = [&](int u,int v){
        res[u]&=res[v];
        if((int)s[u].size()<(int)s[v].size()) s[u].swap(s[v]);
        for(auto [d,x]:s[v]) res[u]&=add(u,x);
    };
    for(int i=N-1;i>=0;i--){
        if(i){
            if(c[P[i]].find(C[i])!=c[P[i]].end()) res[P[i]]=0;
            c[P[i]][C[i]]=i;
            sz[P[i]]+=sz[i];
        }
        res[i]&=add(i,i);
        if(i) cal(P[i],i);
    }
    return res;
}
