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
#pragma GCC target("popcnt,lzcnt")

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
const int maxq=1000005;
const int maxl=20;
const int maxa=2000000;
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

int x[maxn][15],dp[maxn][15][15];

void solve(){
    int n,m,k;cin >> n >> m >> k;
    for(int i=0;i<n;i++){
        for(int j=1;j<=m;j++) cin >> x[j][i];
    }
    for(int i=1;i<=m;i++) sort(x[i],x[i]+n,greater<int>());
    for(int i=0;i<=m;i++) for(int j=0;j<k;j++) for(int d=0;d<n;d++) dp[i][j][d]=-inf;
    dp[0][0][0]=0;
    for(int i=1;i<=m-k+1;i++){
        for(int j=0;j<k;j++){
            for(int d=0;d<n;d++){
                if(dp[i-1][j][d]==-inf) continue;
                for(int p=max(i,i-1+j);p<i+k;p++){
                    int nd=(p==i-1+j?d+1:0);
                    if(nd!=n) dp[i][p-i][nd]=max(dp[i][p-i][nd],dp[i-1][j][d]+x[p][nd]);
                }

            }
        }
    }
    int ans=0;
    for(int i=0;i<k;i++) for(int j=0;j<n;j++) ans=max(ans,dp[m-k+1][i][j]);
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
