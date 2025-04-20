#include "werewolf.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
const int maxl=20;
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second

int par[maxn];
int findpar(int u){
    if(u!=par[u]) return par[u]=findpar(par[u]);
    return u;
}

struct Tree{
    vector<int> edge[maxn];
    int n,L[maxn],R[maxn],num,p[maxn][maxl];
    void add(int u,int v){
        par[v]=p[v][0]=u;
        edge[u].push_back(v);
    }
    void dfs(int u){
        L[u]=++num;
        for(int i=1;i<18;i++) p[u][i]=p[p[u][i-1]][i-1];
        for(int v:edge[u]) dfs(v);
        R[u]=num;
    }
    void build(vector<pii> e,int root){
        for(int i=1;i<=n;i++) par[i]=i;
        for(auto &[u,v]:e){
            u=findpar(u);v=findpar(v);
            if(u!=v) add(u,v);
        }
        dfs(root);
    }
    int get(int u,int l,int r){
        for(int i=17;i>=0;i--) if(p[u][i]>=l && p[u][i]<=r) u=p[u][i];
        return u;
    }
}T1,T2;

namespace BIT{
    int n,bit[maxn];
    void update(int x){
        for(int i=x;i<=n;i+=(i&(-i))) bit[i]++;
    }
    int query(int x){
        int res=0;
        for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
        return res;
    }
}

vector<int> check_validity(int N, vector<int> U, vector<int> V,
                                vector<int> s, vector<int> t,
                                vector<int> l, vector<int> r) {
    int m=(int)U.size();
    T1.n=T2.n=BIT::n=N;

    vector<pii> e;
    for(int i=0;i<m;i++){
        U[i]++;V[i]++;
        if(U[i]>V[i]) swap(U[i],V[i]);
        e.push_back({U[i],V[i]});
    }
    sort(e.begin(),e.end(),greater<pii>());
    T1.build(e,1);

    e.clear();
    for(int i=0;i<m;i++) e.push_back({V[i],U[i]});
    sort(e.begin(),e.end());
    T2.build(e,N);

    int q=(int)s.size();
    vector<int> ans(q);
    vector<piii> query;
    for(int i=1;i<=N;i++) query.push_back({{T1.L[i],T2.L[i]},-q-1});
    for(int i=0;i<q;i++){
        s[i]++;t[i]++;l[i]++;r[i]++;
        s[i]=T1.get(s[i],l[i],N);
        t[i]=T2.get(t[i],1,r[i]);
        query.push_back({{T1.R[s[i]],T2.R[t[i]]},i+1});
        query.push_back({{T1.L[s[i]]-1,T2.R[t[i]]},-i-1});
        query.push_back({{T1.R[s[i]],T2.L[t[i]]-1},-i-1});
        query.push_back({{T1.L[s[i]]-1,T2.L[t[i]]-1},i+1});
    }
    sort(query.begin(),query.end());
    for(auto &[d,id]:query){
        if(id==-q-1) BIT::update(d.se);
        else ans[abs(id)-1]+=(id<0?-1:1)*BIT::query(d.se);
    }

    for(int i=0;i<q;i++) ans[i]=(ans[i]>=1);
    return ans;
}
