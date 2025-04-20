#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;

int N;
struct dsu{
    bool check=true;
    int cnt,par[maxn],sz[maxn],dd[maxn];
    dsu(){};
    void init(){
        cnt=N;check=true;
        for(int i=0;i<N;i++) par[i]=i,sz[i]=1;
    }
    int findpar(int u){
        if(u!=par[u]) return par[u]=findpar(par[u]);
        return u;
    }
    void unions(int u,int v){
        dd[u]++,dd[v]++;
        if(dd[u]>=3 || dd[v]>=3) check=false,cnt=0;
        u=findpar(u);v=findpar(v);
        if(u==v){
            if(!check) cnt=0;
            else cnt=sz[u];
            check=false;
            return;
        }
        if(sz[u]<sz[v]) swap(u,v);
        sz[u]+=sz[v];par[v]=u;
    }
};
int mx=0;
vector<pair<int,int>> e;
vector<int> V;
dsu D[5],S;

void Init(int N_) {
  N = N_;
  S.init();
}

void Link(int A, int B) {
    S.unions(A,B);
    mx=max({mx,S.dd[A],S.dd[B]});
    e.push_back({A,B});
    if(mx>=3){
        if(V.empty()){
            int x=A;
            if(S.dd[x]!=3) x=B;
            for(auto [u,v]:e) if(u==x || v==x) V.push_back(u^v^x);
            V.push_back(x);
            for(int i=0;i<4;i++){
                D[i].init();
                for(auto [u,v]:e) if(u!=V[i] && v!=V[i]) D[i].unions(u,v);
            }
        }
        else{
            for(int i=0;i<4;i++){
                if(A==V[i] || B==V[i]) continue;
                D[i].unions(A,B);
            }
        }
    }
}

int CountCritical() {
    if(mx<=2) return S.cnt;
    int total=0;
    for(int i=0;i<4;i++){
        total+=D[i].check;
        //if(D[i].check) cout << '*' << V[i] << '\n';
    }
    return total;
}
