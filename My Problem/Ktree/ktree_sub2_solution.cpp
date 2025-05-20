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
#define ll long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const ll inf=1e18;
const int mod=998244353;
const int maxn=200005;
const int B=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;
const int S=4;
 
struct node{
    ll val[4];
    node(){
        for(int i=0;i<S;i++) val[i]=-inf;
    }
    void del(ll x){
        for(int i=0;i<S;i++) if(val[i]!=-inf) val[i]-=x;
    }
    void add(ll x){
        for(int i=0;i<S;i++) if(x>val[i]) swap(x,val[i]);
    }
    node operator+(const node &a){
        node res;
        int p=0,pa=0;
        for(int i=0;i<S;i++){
            if(p==S) res.val[i]=a.val[pa++];
            else if(pa==S) res.val[i]=val[p++];
            else if(val[p]>a.val[pa]) res.val[i]=val[p++];
            else res.val[i]=a.val[pa++];
        }
        return res;
    }
};
 
int n,q,c[maxn],dep[maxn];
ll dd[maxn];
vector<pii> edge[maxn];
int Min[2*maxn][maxl],lg2[2*maxn],P[maxn],pos;
int L[maxn],R[maxn],T,cn[maxn];
 
void dfs(int u,int p){
    dep[u]=dep[p]+1;
    L[u]=++T;cn[T]=u;
    Min[++pos][0]=u;P[u]=pos;
    for(auto [v,w]:edge[u]){
        if(v==p) continue;
        dd[v]=dd[u]+w;
        dfs(v,u);
        Min[++pos][0]=u;
    }
    R[u]=T;
}
 
int cmp(int u,int v){
    return (L[u]<L[v]?u:v);
}
 
int lca(int u,int v){
    u=P[u];v=P[v];
    if(u>v) swap(u,v);
    int p=lg2[v-u+1];
    return cmp(Min[u][p],Min[v-(1<<p)+1][p]);
}
 
ll dist(int u,int v){
    return dd[u]+dd[v]-2*dd[lca(u,v)];
}
 
void solve(){
    cin >> n >> q;
    for(int i=1;i<=n;i++) cin >> c[i];
    for(int i=1;i<n;i++){
        int u,v,w;cin >> u >> v >> w;
        edge[u].push_back({v,w});
        edge[v].push_back({u,w});
    }
    dfs(1,0);
    for(int i=2;i<=pos;i++) lg2[i]=lg2[i/2]+1;
    for(int i=1;i<20;i++){
        for(int j=1;j<=(pos-(1<<i)+1);j++) Min[j][i]=cmp(Min[j][i-1],Min[j+(1<<(i-1))][i-1]);
    }
 
    for(int i=1;i<=q;i++){
        int op;cin >> op;
        if(op==1){
            int u;cin >> u;
            c[u]^=1;
        }
        else{
            int u,v,t,k;cin >> u >> v >> t >> k;
            node res=node();
            for(int x=L[u];x<=R[u];x++) if(c[cn[x]]==t) res.add(dist(v,cn[x]));
            for(int j=0;j<k;j++) cout << res.val[j] << ' ';
            cout << '\n';
        }
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
