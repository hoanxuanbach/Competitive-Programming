#include "split.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
#define pii pair<int,int>
#define fi first
#define se second
vector<int> edge[maxn],tree[maxn];
int low[maxn],num[maxn],sz[maxn],T;
bool del[maxn],vis[maxn];

void pre_dfs(int u,int p){
    sz[u]=1;
    low[u]=num[u]=++T;
    for(int v:edge[u]){
        if(v==p) continue;
        if(!num[v]){
            pre_dfs(v,u);
            sz[u]+=sz[v];
            tree[u].push_back(v);
            low[u]=min(low[u],low[v]);
            //cout << "tree " << u << ' ' << v << '\n';
        }
        else low[u]=min(low[u],num[v]);
    }
}

vector<int> find_split(int n, int A, int B, int C, vector<int> U, vector<int> V) {
    int m=(int)U.size();
    vector<pii> S={{A,1},{B,2},{C,3}};
    sort(S.begin(),S.end());
    for(int i=0;i<m;i++){
        edge[U[i]].push_back(V[i]);
        edge[V[i]].push_back(U[i]);
    }
    pre_dfs(0,0);

    int x=0;
    bool check=true;
    while(check){
        check=false;
        for(int v:tree[x]) if(sz[v]>=S[0].fi){
            x=v,check=true;
            break;
        }
    }
    vector<int> c(n,S[2].se);
    function<void(int)> color = [&](int u){
        vis[u]=true;
        if(S[1].fi) c[u]=S[1].se,S[1].fi--;
        for(int v:tree[u]) color(v);
    };
    function<void(int)> color2 = [&](int u){
        vis[u]=true;
        if(S[0].fi) c[u]=S[0].se,S[0].fi--;
        for(int v:edge[u]) if(!vis[v]) color2(v);
    };
    int ss=sz[x];
    for(int v:tree[x]){
        if(low[v]<num[x] && ss-sz[v]>=S[0].fi){
            del[v]=true;
            ss-=sz[v];
        }
    }
    if(n-ss>=S[1].fi) swap(S[0],S[1]);
    if(n-ss>=S[0].fi){
        S[1].fi--;
        c[x]=S[1].se;
        vis[x]=true;
        for(int v:tree[x]) if(!del[v]) color(v);
        for(int i=0;i<n;i++) if(!vis[i]){
            color2(i);
            break;
        }
    }
    else return vector<int>(n,0);
    return c;
}
