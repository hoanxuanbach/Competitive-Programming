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
#define ld long double
#define pii pair<int,int>
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e9;
const int mod=998244353;
const int maxn=500005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;

int n,k,c[maxn],d[maxn],dep[maxn],par[maxn];
bool del[maxn];
vector<int> edge[maxn];
vector<int> sheep;

void dfs(int u,int p){
    dep[u]=dep[p]+1;par[u]=p;
    if(c[u]) sheep.push_back(u);
    for(int v:edge[u]) if(v!=p) dfs(v,u);
}

void bfs(int u){
    del[u]=true;
    for(int v:edge[u]) if(!del[v] && d[v]<d[u]) bfs(v);
}

void solve(){
    cin >> n >> k;
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    for(int i=1;i<=k;i++){
        int x;cin >> x;
        c[x]=1;
    }
    dfs(1,0);
    queue<int> q;
    for(int i=1;i<=n;i++){
        if(c[i]) d[i]=0,q.push(i);
        else d[i]=-1;
    }
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int v:edge[u]){
            if(d[v]==-1){
                d[v]=d[u]+1;
                q.push(v);
            }
        }
    }
    sort(sheep.begin(),sheep.end(),[=](int x,int y){return dep[x]>dep[y];});
    vector<int> ans;
    for(int x:sheep){
        if(del[x]) continue;
        int u=x;
        while(par[u] && d[par[u]]==dep[x]-dep[par[u]]) u=par[u];
        ans.push_back(u);
        bfs(u);
    }
    cout << (int)ans.size() << '\n';
    for(int v:ans) cout << v << ' ';
    cout << '\n';
}

signed main(){
    //freopen("SHEEP.INP","r",stdin);
    //freopen("SHEEP.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
