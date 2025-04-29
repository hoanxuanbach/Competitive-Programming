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
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int maxn=100005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
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

namespace Tree{
    vector<vector<int>> edge,Min;
    vector<int> lg2,dep,L,R;
    int pos;
    int cmp(int u,int v){
        return (dep[u]<dep[v]?u:v);
    }
    int lca(int u,int v){
        u=L[u];v=L[v];
        if(u>v) swap(u,v);
        int p=lg2[v-u+1];
        return cmp(Min[u][p],Min[v-(1<<p)+1][p]);
    }
    int dist(int u,int v){
        return dep[u]+dep[v]-2*dep[lca(u,v)];
    }
    void dfs(int u,int p){
        L[u]=++pos;Min[pos][0]=u;
        dep[u]=dep[p]+1;
        for(int v:edge[u]){
            if(v==p) continue;
            dfs(v,u);Min[++pos][0]=u;
        }
        R[u]=pos;
    }
    void init(int n){
        lg2.assign(2*n+1,0);
        dep.assign(n+1,0);
        L.assign(n+1,0);
        R.assign(n+1,0);
        edge.resize(n+1);
        Min.assign(2*n+1,vector<int>(maxl,0));
    }
    void build(int n){
        dfs(1,0);
        for(int i=2;i<=pos;i++) lg2[i]=lg2[i/2]+1;
        for(int i=1;i<20;i++){
            for(int j=1;j<=(pos-(1<<i)+1);j++) Min[j][i]=cmp(Min[j][i-1],Min[j+(1<<(i-1))][i-1]);
        }
    }
}

int n,m,dd[maxn];
bool vis[maxn];
vector<pii> adj[maxn],rev_adj[maxn];
vector<pii> adj2[maxn];


void dfs(int u){
    vis[u]=1;
    for(auto [v,w]:adj[u]){
        if(vis[v]) continue;
        dd[v]=dd[u]*w%mod;
        Tree::edge[u].push_back(v);
        dfs(v);
    }
}

int dp[maxn];

int dfs2(int u,int t){
    if(u==t) return dp[u]=1;
    sort(adj2[u].begin(),adj2[u].end(),[&](pii x,pii y){return Tree::L[x.fi]<Tree::L[y.fi];});
    dp[u]=0;
    for(auto [v,w]:adj2[u]) dp[u]=(dp[u]+(1-dp[u]+mod)*w%mod*dfs2(v,t))%mod;
    return dp[u];
}

int cal(int s){
    vector<int> node;
    for(auto [v,w]:rev_adj[s]){
        if(Tree::L[s]<=Tree::L[v] && Tree::L[v]<=Tree::R[s]) continue;
        node.push_back(v);
        adj2[v].push_back({s,w});
    }
    sort(node.begin(),node.end(),[&](int x,int y){return Tree::L[x]<Tree::L[y];});
    int sz=(int)node.size();
    for(int i=0;i<sz-1;i++) node.push_back(Tree::lca(node[i],node[i+1]));
    sort(node.begin(),node.end());
    node.erase(unique(node.begin(),node.end()),node.end());
    sort(node.begin(),node.end(),[&](int x,int y){return Tree::L[x]<Tree::L[y];});
    int root=s;
    vector<int> v;
    for(int u:node){
        while(!v.empty() && Tree::R[v.back()]<Tree::L[u]) v.pop_back();
        if(!v.empty()) adj2[v.back()].push_back({u,dd[u]*power(dd[v.back()],mod-2)%mod});
        else root=u;
        v.push_back(u);
    }
    dfs2(root,s);
    for(int u:node) adj2[u].clear();
    return dp[root]*dd[root]%mod;
}

void solve(){
    cin >> n >> m;
    Tree::init(n);
    for(int i=1;i<=m;i++){
        int u,v,a,b;cin >> u >> v >> a >> b;
        a=a*power(b,mod-2)%mod;
        adj[u].push_back({v,a});
        rev_adj[v].push_back({u,a});
    }
    dd[1]=1;dfs(1);
    Tree::build(n);
    for(int i=1;i<=n;i++) cout << cal(i) << '\n';
    cout << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
