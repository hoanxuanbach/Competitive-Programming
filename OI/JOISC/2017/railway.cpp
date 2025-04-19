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
const int maxn=100005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=500005;
const int maxl=18;
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
const int base=104729;
void solve(){
    int n,k,q;cin >> n >> k >> q;
    vector<int> a(n+1);
    vector<vector<pii>> p(n+1,vector<pii>(maxl,{0,0}));
    for(int i=1;i<=n;i++) cin >> a[i];
    vector<int> v;
    for(int i=1;i<=n;i++){
        while(!v.empty() && a[v.back()]<a[i]) v.pop_back();
        p[i][0].fi=(v.empty()?i:v.back());
        v.push_back(i);
    }
    v.clear();
    for(int i=n;i>=1;i--){
        while(!v.empty() && a[v.back()]<a[i]) v.pop_back();
        p[i][0].se=(v.empty()?i:v.back());
        v.push_back(i);
    }
    auto unions = [&](pii x,pii y){
        return make_pair(min(x.fi,y.fi),max(x.se,y.se));
    };
    for(int i=1;i<maxl;i++){
        for(int j=1;j<=n;j++) p[j][i]=unions(p[p[j][i-1].fi][i-1],p[p[j][i-1].se][i-1]);
    }
    for(int i=1;i<=q;i++){
        int s,t;cin >> s >> t;
        if(s>t) swap(s,t);
        int l=s,r=s,ans=0;
        for(int j=maxl-1;j>=0;j--){
            if(max(p[l][j].se,p[r][j].se)<t){
                ans+=(1<<j);
                tie(l,r)=unions(p[l][j],p[r][j]);
            }
        }
        int m=r;l=r=t;
        for(int j=maxl-1;j>=0;j--){
            if(min(p[l][j].fi,p[r][j].fi)>m){
                ans+=(1<<j);
                tie(l,r)=unions(p[l][j],p[r][j]);
            }
        }
        cout << ans << '\n';
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
