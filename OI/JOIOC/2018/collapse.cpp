#include "collapse.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
const int B=320;
#define pii pair<int,int>
#define fi first
#define se second

vector<pii> e[maxn];
vector<int> cc[maxn],pp[maxn];

struct DSU{
    int par[maxn],sz[maxn],cnt=0;
    vector<pii> event;
    DSU(int n){
        cnt=0;
        for(int i=0;i<n;i++) par[i]=i,sz[i]=1;
    }
    void init(int n){
        cnt=0;
        for(int i=0;i<n;i++) par[i]=i,sz[i]=1;
    }
    int findpar(int u){
        if(u!=par[u]) return findpar(par[u]);
        return u;
    }
    void unions(int u,int v){
        u=findpar(u);v=findpar(v);
        if(u==v){
            event.push_back({-1,-1});
            return;
        }
        if(sz[u]<sz[v]) swap(u,v);
        par[v]=u;sz[u]+=sz[v];cnt++;
        event.push_back({u,v});
    }
    void roll_back(){
        pii x=event.back();
        event.pop_back();
        if(x.fi==-1) return;
        int u=x.fi,v=x.se;
        par[v]=v;sz[u]-=sz[v];cnt--;
    }
};

std::vector<int> simulateCollapse(
	int N,
	std::vector<int> T,
	std::vector<int> X,
	std::vector<int> Y,
	std::vector<int> W,
	std::vector<int> P
) {
    int C=(int)T.size(),Q=(int)W.size();
    vector<int> res(Q,0);
    vector<vector<int>> qq(C);
    for(int i=0;i<Q;i++) qq[W[i]].push_back(i);
    DSU dsu(N);
    set<pii> ss;
    for(int i=0;i<C;i+=B){
        set<pii> st;
        for(int j=i;j<min(i+B,C);j++){
            if(X[j]>Y[j]) swap(X[j],Y[j]);
            if(ss.find({X[j],Y[j]})!=ss.end()){
                ss.erase({X[j],Y[j]});
                st.insert({X[j],Y[j]});
            }
        }

        for(int j=0;j<N;j++) pp[j].clear();
        for(int j=i;j<min(i+B,C);j++){
            if(T[j]) st.erase({X[j],Y[j]});
            else st.insert({X[j],Y[j]});
            for(pii x:st) e[j].push_back(x);
            for(int id:qq[j]) pp[P[id]].push_back(id);
        }

        dsu.init(N);
        for(int j=0;j<N;j++) cc[j].clear();
        for(pii x:ss) cc[x.se].push_back(x.fi);

        for(int j=0;j<N;j++){
            for(int u:cc[j]) dsu.unions(u,j);
            for(int id:pp[j]){
                for(pii x:e[W[id]]) if(max(x.fi,x.se)<=j) dsu.unions(x.fi,x.se);
                res[id]+=dsu.cnt;
                for(pii x:e[W[id]]) if(max(x.fi,x.se)<=j) dsu.roll_back();
            }
        }

        dsu.init(N);
        for(int j=0;j<N;j++) cc[j].clear();
        for(pii x:ss) cc[x.fi].push_back(x.se);

        for(int j=N-1;j>=0;j--){
            for(int id:pp[j]){
                for(pii x:e[W[id]]) if(min(x.fi,x.se)>j) dsu.unions(x.fi,x.se);
                res[id]+=dsu.cnt;
                for(pii x:e[W[id]]) if(min(x.fi,x.se)>j) dsu.roll_back();
            }
            for(int u:cc[j]) dsu.unions(u,j);
        }

        for(pii x:st) ss.insert(x);
    }
    for(int i=0;i<Q;i++) res[i]=N-res[i];
    return res;
}
