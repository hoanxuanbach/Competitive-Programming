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
#define ld long double
#define pii pair<int,int>
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int mod=998244353;
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=200005;
const int root=3;
const int base=101;

int p[maxa+5];
int n,a[maxn],dp[maxn],Max[maxn];

void solve(){
    for(int i=2;i<=maxa;i++){
        if(!p[i]){
            for(int j=i*2;j<=maxa;j+=i) p[j]=1;
        }
    }
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=n;i++){
        dp[i]=Max[max(0,i-6)]+1;
        if(i>=2 && !p[a[i-1]+a[i]]) dp[i]=max(dp[i],dp[i-1]+1);
        for(int j=2;j<=min(i-1,5);j++){
            if((a[i-j]^a[i]^j)&1){
                if(!p[a[i-j]+1] && !p[a[i]+1]) dp[i]=max(dp[i],dp[i-j]+1);
                else if(j>=3 && (a[i]==1 || a[i-j]==1)) dp[i]=max(dp[i],dp[i-j]+1);
                else if(j>=4 && (!p[a[i]+1] || !p[a[i-j]+1])) dp[i]=max(dp[i],dp[i-j]+1);
                else if(j>=5 && (a[i]&1)) dp[i]=max(dp[i],dp[i-j]+1);
            }
            else dp[i]=max(dp[i],dp[i-j]+1);
        }
        Max[i]=max(dp[i],Max[i-1]);
    }
    cout << n-Max[n] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
