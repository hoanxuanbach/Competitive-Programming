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
const int maxn=200005;
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
    int a=0,b=1;
    frac(int _a=0,int _b=1):a(_a),b(_b){
        int g=__gcd(a,b);
        a/=g;b/=g;
    }
    friend bool operator<(frac x,frac y){
        return (__int128)x.a*y.b<(__int128)x.b*y.a;
    }
    friend bool operator>(frac x,frac y){
        return (__int128)x.a*y.b>(__int128)x.b*y.a;
    }
};
void solve(){
    int n,l;cin >> n >> l;
    vector<vector<frac>> f(n+1,vector<frac>(n+1));
    vector<bool> check(n+1,false);
    for(int i=1;i<=n;i++){
        int sum=0;vector<int> v(l+1,0);
        for(int j=1;j<=l;j++) cin >> v[j],sum+=v[j],v[j]*=n;
        int cur=0,ss=0;
        for(int j=1;j<=n;j++){
            ss+=sum;
            while(v[cur]<ss) ss-=v[cur++];
            f[i][j]=frac((cur-1)*v[cur]+ss,v[cur]);
        }
    }
    vector<pair<frac,int>> ans;
    for(int i=1;i<=n;i++){
        pair<frac,int> Min={frac(inf,1),0};
        for(int j=1;j<=n;j++){
            if(check[j]) continue;
            Min=min(Min,mpp(f[j][i],j));
        }
        ans.push_back(Min);check[Min.se]=1;
    }
    for(int i=0;i<n-1;i++) cout << ans[i].fi.a << ' ' << ans[i].fi.b << '\n';
    for(int i=0;i<n;i++) cout << ans[i].se << ' ';
    cout << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
