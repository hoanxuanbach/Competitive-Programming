#include "circuit.h"
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 2e5+5;
const int mod = 1e9+2022;
int N,M,sz[maxn],suf[maxn],dp[maxn];
vector<int> A;
vector<int> edge[maxn];

struct node{
    int lazy=0;
    int total[2];
    node(){
        memset(total,0,sizeof(total));
    }
    friend node operator+(node a,node b){
        node res;
        for(int i=0;i<=1;i++) res.total[i]=(a.total[i]+b.total[i])%mod;
        return res;
    }
}tree[2*maxn];

void build(int l,int r,int id){
    if(l==r){
        tree[id].total[A[l]]=dp[N+l];
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    tree[id]=tree[id<<1]+tree[id<<1|1];
}

void getnew(int id){
    tree[id].lazy^=1;
    swap(tree[id].total[0],tree[id].total[1]);
}
void pushdown(int id){
    if(tree[id].lazy){
        getnew(id<<1);
        getnew(id<<1|1);
        tree[id].lazy=0;
    }
}
void update(int l,int r,int id,int tl,int tr){
    if(tr<l || r<tl) return;
    if(tl<=l && r<=tr){
        getnew(id);
        return;
    }
    pushdown(id);
    int mid=(l+r)>>1;
    update(l,mid,id<<1,tl,tr);update(mid+1,r,id<<1|1,tl,tr);
    tree[id]=tree[id<<1]+tree[id<<1|1];
}

void init(int _N, int _M, vector<int> P, vector<int> _A) {
    N=_N;M=_M;A=_A;
    for(int i=1;i<N+M;i++){
        edge[P[i]].push_back(i);
        sz[P[i]]++;
    }
    function<void(int)> pre_dfs = [&](int u){
        dp[u]=max(sz[u],1);
        for(int v:edge[u]) pre_dfs(v),dp[u]=1LL*dp[u]*dp[v]%mod;
        //cout << "dp " << u << ' ' << dp[u] << '\n';
    };
    pre_dfs(0);
    function<void(int)> dfs = [&](int u){
        int cur=1;
        for(int i=(int)edge[u].size()-1;i>=0;i--){
            int v=edge[u][i];suf[v]=cur;
            cur=1LL*cur*dp[v]%mod;
        }
        cur=1;
        for(int v:edge[u]){
            int cc=dp[v];
            dp[v]=1LL*cur*suf[v]%mod*dp[u]%mod;
            dfs(v);cur=1LL*cur*cc%mod;
        }
    };
    dp[0]=1;dfs(0);
    //for(int i=0;i<N+M;i++) cout << dp[i] << ' ';
    //cout << '\n';
    build(0,M-1,1);
}

int count_ways(int L, int R) {
    update(0,M-1,1,L-N,R-N);
    return tree[1].total[1];
}
