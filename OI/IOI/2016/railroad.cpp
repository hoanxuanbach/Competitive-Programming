#include "railroad.h"
#include<bits/stdc++.h>
using namespace std;
const int inf = 1e9;

long long plan_roller_coaster(std::vector<int> s, std::vector<int> t) {
    long long res=0;
    vector<int> com;
    s.push_back(inf);
    t.push_back(0);
    int n=(int)s.size();
    for(int i=0;i<n;i++) com.push_back(s[i]),com.push_back(t[i]);
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    int sz=(int)com.size();
    vector<int> cnt(sz),par(sz);
    iota(par.begin(),par.end(),0);
    function<int(int)> findpar = [&](int u){
        if(u!=par[u]) return par[u]=findpar(par[u]);
        return u;
    };
    auto unions = [&](int u,int v){
        u=findpar(u);v=findpar(v);
        if(u!=v) par[v]=u;
        return (u!=v);
    };
    for(int i=0;i<n;i++){
        int l=lower_bound(com.begin(),com.end(),s[i])-com.begin();
        int r=lower_bound(com.begin(),com.end(),t[i])-com.begin();
        cnt[l]++;cnt[r]--;unions(l,r);
    }
    for(int i=1;i<sz;i++){
        cnt[i]+=cnt[i-1];
        if(cnt[i-1]){
            unions(i-1,i);
            if(cnt[i-1]>0) res+=1LL*cnt[i-1]*(com[i]-com[i-1]);
        }
    }
    vector<pair<int,int>> e;
    for(int i=1;i<sz;i++) e.push_back({com[i]-com[i-1],i});
    sort(e.begin(),e.end());
    for(auto [x,i]:e) if(unions(i-1,i)) res+=x;
    return res;
}
