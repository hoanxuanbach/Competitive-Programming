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
const int mod=1e9+7;
const int maxn=400005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=250000;
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
const int base=101;
struct BIT{
    int n;
    vector<int> bit;
    void init(int N){
        n=N;
        bit.assign(n+1,0);
    }
    int query(int x){
        int res=0;
        for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
        return res;
    }
    void update(int x,int val){
        for(int i=x;i<=n;i+=(i&(-i))) bit[i]+=val;
    }
    void update_range(int l,int r,int val){
        update(l,val);update(r+1,-val);
    }
}ft,fs;
void solve(){
    int n,q;cin >> n >> q;
    vector<vector<int>> edge(n+1),par(n+1,vector<int>(maxl,0));
    vector<int> dep(n+1,0),L(n+1),R(n+1);
    vector<int> use(n+1,0);
    int pos=0;
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    function<void(int,int)> dfs = [&](int u,int p){
        dep[u]=dep[p]+1;par[u][0]=p;L[u]=++pos;
        for(int i=1;i<maxl;i++) par[u][i]=par[par[u][i-1]][i-1];
        for(int v:edge[u]){
            if(v==p) continue;
            dfs(v,u);
        }
        R[u]=pos;
    };
    dfs(1,0);
    ft.init(n);fs.init(n);
    auto jmp = [=](int u){
        for(int i=maxl-1;i>=0;i--){
            int p=par[u][i];
            if(p==0) continue;
            else if(dep[u]-dep[p]==ft.query(L[u])-ft.query(L[p])) u=p;
        }
        return u;
    };
    for(int i=1;i<=n;i++){
        fs.update(L[i],1);
        ft.update_range(L[i],R[i],1);
        use[i]=1;
    }
    for(int i=1;i<=q;i++){
        int id,v;cin >> id >> v;
        if(id==1){
            int num=fs.query(R[v])-fs.query(L[v]-1),u=par[v][0],p=par[jmp(u)][0];
            //cout << v << ' ' << u << ' ' << num << '\n';
            if(use[v]){
                fs.update(L[u],-num);
                ft.update_range(L[v],R[v],-1);
                if(p) fs.update(L[p],num);
            }
            else{
                fs.update(L[u],num);
                ft.update_range(L[v],R[v],1);
                if(p) fs.update(L[p],-num);
            }
            use[v]^=1;
        }
        else{
            v=jmp(v);
            cout << fs.query(R[v])-fs.query(L[v]-1) << '\n';
        }
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
