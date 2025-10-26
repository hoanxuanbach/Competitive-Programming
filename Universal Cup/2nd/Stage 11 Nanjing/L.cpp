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
const int maxn=200005;
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

void solve(){
    int n,k;cin >> n >> k;k/=2;
    vector<pii> p1,p2;
    for(int i=1;i<=n;i++){
        int c,w,f;cin >> c >> w >> f;
        if(w==1) p1.push_back({f,c});
        else p2.push_back({f,c});
    }
    sort(p1.begin(),p1.end(),greater<pii>());
    int d=-1;
    for(pii x:p1){
        if(d!=-1){
            x.se--;
            p2.push_back({d,1});
            d=-1;
        }
        if(x.se>=2) p2.push_back({x.fi,x.se/2});
        if(x.se&1) d=x.fi;
    }
    if(d!=-1) p2.push_back({d,1});
    sort(p2.begin(),p2.end(),greater<pii>());

    d=0;
    int cur=-1,res=0;
    for(pii x:p2){
        if(cur!=-1){
            d+=x.se;
            if(d>=k) d-=k,res+=cur,cur=x.fi;
        }
        else cur=x.fi,d=x.se;
        res+=cur*(d/k);d%=k;
        if(d==0) cur=-1;
    }
    if(d) res+=cur;
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
