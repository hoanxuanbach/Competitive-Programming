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
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int mod=998244353;
const int maxn=50005;
const int bl=200;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
const int base=131;

int n,m,num[maxm];
vector<int> adj[maxn],edge[maxn];
bool check[maxn];
int par[maxn];

int findpar(int u){
    if(u!=par[u]) return par[u]=findpar(par[u]);
    return u;
}

int unions(int u,int v){
    u=findpar(u);v=findpar(v);
    if(u==v) return false;
    return par[v]=u,true;
}

void solve(){
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        int sz;cin >> sz;
        adj[i].resize(sz);
        for(int j=0;j<sz;j++){
            cin >> adj[i][j];
            num[adj[i][j]]^=i;
        }
    }
    for(int i=1;i<=n;i++){
        for(int &x:adj[i]) x=num[x]^i;
        if((int)adj[i].size()>bl){
            for(int x:adj[i]) if((int)adj[x].size()>bl) edge[i].push_back(x);
        }
        else edge[i]=adj[i];
    }
    int q;cin >> q;
    for(int i=1;i<=q;i++){
        int sz;cin >> sz;
        vector<int> v(sz);
        int S=sz,V=sz,E=0;
        for(int &x:v){
            cin >> x;
            check[x]=true;
            par[x]=x;
        }
        for(int x:v){
            for(int u:edge[x]){
                if(!check[u]) continue;
                int t=(((int)adj[u].size()<=bl) == ((int)adj[x].size()<=bl));
                if(!t || u<x){
                    E++;
                    S-=unions(u,x);
                }
            }
        }
        cout << S+E-V << '\n';
        for(int x:v) check[x]=false;
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}

