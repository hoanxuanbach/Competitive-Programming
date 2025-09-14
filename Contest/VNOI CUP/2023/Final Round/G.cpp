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
const int maxn=150005;
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
struct frac{
    int a,b,id;
    frac(int a=-1,int b=-1,int id=-1):a(a),b(b),id(id){}
    friend bool operator<(frac x,frac y){
        if(x.a*y.b!=x.b*y.a) return x.a*y.b<x.b*y.a;
        else return x.id<y.id;
    }
    friend bool operator>(frac x,frac y){
        if(x.a*y.b!=x.b*y.a) return x.a*y.b>x.b*y.a;
        else return x.id>y.id;
    }
};
int p[maxn],par[maxn],t[maxn],cost[maxn],w[maxn];
set<frac> ss;
int findpar(int u){
    if(u!=par[u]) return par[u]=findpar(par[u]);
    return u;
}
void solve(){
    int n,ans=0;cin >> n;
    for(int i=1;i<=n;i++){
        cin >> w[i];ans+=w[i]*(n+1);
        cost[i]=w[i],t[i]=1,par[i]=i;
    }
    for(int i=2;i<=n;i++){
        cin >> p[i];
        ss.insert(frac(w[i],t[i],i));
    }
    for(int i=1;i<n;i++){
        int u=ss.begin()->id;ss.erase(ss.begin());
        int d=findpar(p[u]);
        if(d!=1) ss.erase(frac(w[d],t[d],d));
        w[d]+=w[u];cost[d]+=cost[u]+w[u]*t[d];t[d]+=t[u];par[u]=d;
        if(d!=1) ss.insert(frac(w[d],t[d],d));
        /*
        cout << u << '\n';
        for(auto x:ss) cout << x.a << ' ' << x.b << ' ' << x.id << '\n';
        cout << '\n';
        */
    }
    cout << ans-cost[1] << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
