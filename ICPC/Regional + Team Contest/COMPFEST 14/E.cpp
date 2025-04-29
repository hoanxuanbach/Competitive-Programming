// Judges with GCC >= 12 only needs Ofast
// #pragma GCC optimize("O3,no-stack-protector,fast-math,unroint-loops,tree-vectorize")
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
typedef tree<int,nuint_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
- insert(x),erase(x)
- find_by_order(k): return iterator to the k-th smaintest element
- order_of_key(x): the number of elements that are strictly smainter
*/
#pragma GCC target("popcnt,lzcnt")

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
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=21;
const int maxa=200000;
const int root=3;
const int base=101;

vector<int> edge[maxn];
vector<pii> adj[maxn];
int n,q,cnt,len;
int L[maxn],R[maxn],Min[2*maxn][maxl],cn[2*maxn],f[maxn],lg[2*maxn],dep[maxn];

bool cmp(int a,int b){
    return L[a]<L[b];
}
void dfs(int u,int par){
    L[u]=++cnt;len++;
    f[u]=Min[len][0]=len;cn[len]=u;
    dep[u]=dep[par]+1;
    for(int v:edge[u]){
        if(v==par) continue;
        dfs(v,u);
        Min[++len][0]=f[u];
    }
    R[u]=cnt;
}
int lca(int u,int v){
    u=f[u];v=f[v];
    if(u>v) swap(u,v);
    int p=lg[v-u+1],a=min(Min[u][p],Min[v-(1<<p)+1][p]);
    return cn[a];
}
int getdist(int u,int v){
    return dep[u]+dep[v]-2*dep[lca(u,v)];
}
void build(){
    dfs(1,0);
    for(int i=2;i<=len;i++) lg[i]=lg[i/2]+1;
    for(int i=1;i<20;i++){
        for(int j=1;j<=(len-(1<<i)+1);j++) Min[j][i]=min(Min[j][i-1],Min[j+(1<<(i-1))][i-1]);
    }
}


int res=0,sz,child[maxn];

void dfs2(int u,int num){
    for(pii v:adj[u]){
        dfs2(v.fi,v.se);
        child[u]+=child[v.fi];
    }
    //cout << res << '\n';
    //cout << u << ' ' << child[u] << ' ' << sz << ' ' << num << '\n';
    res=(res+(num*(sz-child[u])*(sz-child[u]-1)/2)%mod*child[u])%mod;
    res=(res+(num*(child[u]-1)*child[u]/2)%mod*(sz-child[u]))%mod;
}

void query(int s,vector<int> &xs){
    vector<int> node;sz=s;
    for(int i=0;i<s;i++) node.push_back(xs[i]),child[xs[i]]=1;
    sort(node.begin(),node.end(),cmp);
    for(int i=0;i<s-1;i++) node.push_back(lca(node[i],node[i+1]));
    sort(node.begin(),node.end(),cmp);
    node.erase(unique(node.begin(),node.end()),node.end());
    int root=-1;
    vector<int> v;
    for(int x:node){
        while(!v.empty() && R[v.back()]<L[x]) v.pop_back();
        if(!v.empty()) adj[v.back()].push_back({x,dep[x]-dep[v.back()]});
        else root=x;
        v.push_back(x);
    }
    dfs2(root,0);
    for(int x:node) adj[x].clear(),child[x]=0;
}

vector<int> d[maxn];
int p[maxn];

void solve(){
    int n;cin >> n;
    for(int i=1;i<=n;i++){
        int x;cin >> x;
        d[x].push_back(i);
    }
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    build();
    res=0;
    for(int i=2;i<=maxa;i++){
        if(!p[i]){
            for(int j=i*2;j<=maxa;j+=i){
                p[j]=1;
                for(int x:d[j]) d[i].push_back(x);
            }
            if(!d[i].empty()) query((int)d[i].size(),d[i]);
        }
    }
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}