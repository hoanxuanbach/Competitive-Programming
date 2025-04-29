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
const int inf=1e9;
const int mod=1e9+7;
const int maxn=500005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
int power_mod(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
int power_max(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=min(inf,res*a);
        a=min(a*a,inf);n>>=1;
    }
    return res;
}
const int base=101;

int n,a[maxn],d[maxn];

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        d[i]=a[i-1]-a[i]+1;
        //cout << d[i] << ' ';
    }
    //cout << '\n';
    if(n==1){
        cout << (1LL<<a[1])-1 << '\n';
        return;
    }
    int pos=2;
    for(int i=2;i<=n;i++) if(d[i]>d[pos]) pos=i;
    if(pos+(1LL<<d[pos])<=n || pos-(1LL<<d[pos])>=2){
        cout << -1 << '\n';
        return;
    }
    int cur=(1LL<<d[pos]);
    for(int i=pos+1;i<=n;i++){
        int pre=__builtin_popcountll(cur)-__builtin_popcountll(cur+1)+1;
        if(pre!=d[i]){
            cout << -1 << '\n';
            return;
        }
        cur++;
    }
    cur=(1LL<<d[pos]);
    for(int i=pos;i>=2;i--){
        cur--;
        int pre=__builtin_popcountll(cur)-__builtin_popcountll(cur+1)+1;
        if(pre!=d[i]){
            cout << -1 << '\n';
            return;
        }
    }
    int cc=__builtin_popcountll(cur);
    if(cc>a[1]){
        cout << -1 << '\n';
        return;
    }
    while(__builtin_popcountll(cur)<a[1]){
        d[pos]++;
        cur+=(1LL<<d[pos]);
    }
    cout << cur << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
