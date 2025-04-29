// Judges with GCC >= 12 only needs Ofast
// #pragma GCC optimize("O3,no-stack-protector,fast-math,unroll-loops,tree-vectorize")
// MLE optimization
// #pragma GCC optimize("conserve-stack")
// Old judges
// #pragma GCC target("sse4.2,popcnt,lzcnt,abm,mmx,fma,bmi,bmi2")
// New judges. Test with assert(__builtin_cpu_supports("avx2"));
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native")
// Atcoder
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma")
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
- insert(x),erase(x)
- find_by_order(k): return iterator to the k-th smallest element
- order_of_key(x): the number of elements that are strictly smaller
*/
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int maxn=300005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
const int iroot=power(3,mod-2);
const int base=131;

int n,m,a[maxn],b[maxn],d[maxn],nd[maxn],d1[maxn],d2[maxn];
vector<int> edge[maxn],adj[maxn];
bool vis[maxn];

void dfs(int u){
    vis[u]=true;
    for(int v:adj[u]){
        if(!vis[v]) dfs(v);
        d1[u]=max(d1[u],d1[v]);
        d2[u]=max(d2[u],d2[v]);
    }
}
void dfs2(int u){
    vis[u]=true;
    for(int v:adj[u]){
        if(!vis[v]) dfs2(v);
        nd[u]=max(nd[u],nd[v]);
    }
}

void solve(){
    cin >> n >> m;
    for(int i=1;i<=n;i++) cin >> a[i] >> b[i];
    for(int i=1;i<=m;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    memset(d,-1,sizeof(d));
    queue<int> q;
    d[1]=0;q.push(1);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int v:edge[u]) if(d[v]==-1){
            d[v]=d[u]+1;
            q.push(v);
        }
    }
    pii mx1={-inf,0},mx2={-inf,0};
    for(int i=1;i<=n;i++){
        a[i]-=b[i]*(d[i]+1);
        d1[i]=a[i]+b[i];
        d2[i]=a[i]+2*b[i];
        pii cur={a[i],i};
        if(cur>mx1){
            mx2=mx1;
            mx1=cur;
        }
        else if(cur>mx2) mx2=cur;
    }
    for(int i=1;i<=n;i++) for(int v:edge[i]) if(d[v]==d[i]+1) adj[i].push_back(v);
    dfs(1);
    for(int i=1;i<=n;i++){
        vis[i]=false;nd[i]=-inf;
        for(int v:edge[i]) if(d[v]==d[i]) nd[i]=max(nd[i],d1[v]);
    }
    dfs2(1);
    vector<pii> res;
    for(int v:edge[1]){
        int cur=nd[v];
        for(int x:adj[v]) cur=max(cur,d2[x]);
        if(v==mx1.se) cur=max(cur,mx2.fi);
        else cur=max(cur,mx1.fi);
        res.push_back({v,cur});
    }
    sort(res.begin(),res.end());
    for(pii x:res) cout << x.se << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
