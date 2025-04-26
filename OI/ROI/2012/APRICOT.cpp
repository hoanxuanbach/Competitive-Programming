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
const int maxn=1000005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;

int n,u,r,dp[maxn];

void solve(){
    cin >> n >> r >> u;
    dp[0]=-inf;dp[1]=0;
    for(int i=2;i<n;i++){
        dp[i]=inf;
        int lt=0,rt=i-1,pos=0;
        while(lt<=rt){
            int c=(lt+rt)/2,lb=(i-c+1)/2;
            dp[i]=min(dp[i],max(dp[lb]+u,dp[c]+r));
            if(dp[lb]+u>=dp[c]+r) pos=c+1,lt=c+1;
            else rt=c-1;
        }
        if(pos!=i){
            int lb=(i-pos+1)/2;
            dp[i]=min(dp[i],max(dp[lb]+u,dp[pos]+r));
        }
        /*
        for(int c=0;c<i;c++){
            int lb=(i-c+1)/2,rb=(n-c)/2;
            if(lb<=rb) dp[i]=min(dp[i],max(dp[lb]+u,dp[c]+r));
        }
        */
    }
    int ans=inf;
    for(int c=0;c<n;c++){
        int lb=(n-c+1)/2,rb=(n-c)/2;
        if(lb<=rb) ans=min(ans,max(dp[lb]+u,dp[c]+r));
    }
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();

}
