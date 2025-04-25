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
const int maxn=1000005;
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
const int base=101;
 
int n,b[maxn],p[maxn],u[maxn],a[maxn],g[maxn],f[maxn],d[maxn];
 
void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> b[i],a[i]=b[i];
    for(int i=1;i<n;i++) cin >> p[i];
    for(int i=1;i<n;i++) cin >> u[i];
    for(int i=1;i<n;i++){
        g[i]=p[i]-u[i];
        int h=min(b[i],g[i]);
        b[i]-=h;g[i]-=h;
        if(b[i+1]<g[i]){
            cout << "NO\n";
            return;
        }
        b[i+1]-=g[i];
    }
    cout << "YES\n";
    vector<int> v;
    int res=0;
    for(int i=1;i<n;i++){
        g[i]=p[i];b[i]=0;
        v.push_back(i);
        int x=min(g[i],a[i]);
        g[i]-=x;a[i]-=x;f[i]=x;
        while(a[i+1]<g[i]){
            int pos=v.back();
            int k=min(u[pos],g[i]-a[i+1]);
            d[pos+1]+=k;
            d[i+1]-=k;
            u[pos]-=k;
            if(u[pos]==0) v.pop_back();
            g[i]-=k;
            b[pos]+=k;
            res+=k;
        }
        a[i+1]-=g[i];
        u[i]=min(u[i],g[i]);
    }
    cout << res << '\n';
    for(int i=1;i<n;i++){
        d[i]+=d[i-1];
        f[i]+=d[i];
        cout << f[i] << ' ' << b[i] << ' ' << p[i]-f[i]-b[i] << '\n';
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}