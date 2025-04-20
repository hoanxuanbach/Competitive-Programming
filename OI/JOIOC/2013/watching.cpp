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
//#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
//const int inf=1e18;
const int mod=1e9+7;
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=250000;
const int root=3;
/*
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
const int iroot=power(3,mod-2);
*/
const int base=101;

void solve(){
    int n,p,q;cin >> n >> p >> q;
    vector<int> a(n),nxt0(n),nxt1(n);
    for(int i=0;i<n;i++) cin >> a[i];
    if(p+q>=n){
        cout << 1 << '\n';
        return;
    }
    sort(a.begin(),a.end());
    vector<vector<int>> dp(p+1,vector<int>(q+1,0));
    auto check = [&](int w){
        int c0=0,c1=0;
        for(int i=0;i<n;i++){
            while(c0<n && a[c0]-a[i]<w) c0++;
            while(c1<n && a[c1]-a[i]<2*w) c1++;
            nxt0[i]=c0,nxt1[i]=c1;
        }
        dp.assign(p+1,vector<int>(q+1,0));
        for(int i=0;i<=p;i++){
            for(int j=0;j<=q;j++){
                if(i) dp[i][j]=max(dp[i][j],nxt0[dp[i-1][j]]);
                if(j) dp[i][j]=max(dp[i][j],nxt1[dp[i][j-1]]);
                if(dp[i][j]==n) return true;
            }
        }
        return false;
    };
    int l=1,r=1e9;
    while(r>l){
        int mid=(l+r)>>1;
        if(check(mid)) r=mid;
        else l=mid+1;
    }
    cout << r << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
