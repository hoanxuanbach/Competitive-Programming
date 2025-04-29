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
const int mod=998244353;
const int maxn=5005;
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
const int base=101;

int n,a[maxn],p2[maxn];
int dp[maxn][maxn];

void solve(){
    cin >> n;
    p2[0]=1;
    for(int i=1;i<=n;i++) p2[i]=p2[i-1]*2%mod;
    for(int i=1;i<=n;i++) cin >> a[i];
    dp[1][1]=1;a[1]=n+1;
    for(int i=2;i<=n;i++){
        int sum=0;
        for(int j=i-1;j>=1;j--){
            if(a[i-1]<a[i]) dp[i][j+1]=(dp[i][j+1]+dp[i-1][j])%mod;
            sum=(sum+dp[i-1][j])%mod;
            dp[i][j]=(dp[i][j]+sum)%mod;
        }
        for(int j=1;j<=i;j++) dp[i][j]=dp[i][j]*p2[j-1]%mod;
    }
    int ans=0;
    for(int i=0;i<=n;i++) ans=(ans+dp[n][i])%mod;
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
