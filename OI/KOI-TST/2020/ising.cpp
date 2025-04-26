#include <bits/stdc++.h>
using namespace std;
#define ll long long
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
const int maxn = 250005;
vector<int> edge[maxn];
ll X,A[maxn],C[maxn],vis[maxn];

long long count_ways(int N, std::vector<int> U, std::vector<int> V) {
    for(int i=0;i<(int)U.size();i++){
        edge[U[i]].push_back(V[i]);
        edge[V[i]].push_back(U[i]);
    }
    map<ll,ll> val;
    function<void(int,int)> dfs = [&](int u,int p){
        vis[u]=1;
        //cout << u << ' ' << p << '\n';
        for(int v:edge[u]){
            if(v==p) continue;
            if(!vis[v]){
                C[v]=C[u]^1;
                dfs(v,u);
                A[u]^=A[v];
            }
            else if(vis[v]==1){
                ll x=rng();
                val[x]++;
                A[v]^=x;
                A[u]^=x;
                if(C[u]==C[v]) X^=x;
            }
        }
        val[A[u]]++;
        vis[u]=-1;
    };
    dfs(1,0);
    if(X==0) return 1;
    else if(val.find(X)!=val.end()) return val[X];
    else{
        ll res=0;
        for(auto [x,cnt]:val){
            if(val.find(X^x)!=val.end()) res+=1LL*cnt*val[X^x];
        }
        return res/2;
    }
}
