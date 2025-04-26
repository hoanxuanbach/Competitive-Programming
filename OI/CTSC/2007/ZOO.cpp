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
- insert(x)
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
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int mod2=1e9+7;
const int maxn=10005;
int n,c,dp[maxn][20];
vector<pii> s[maxn];
int cal(int mask){
    for(int j=1;j<=n;j++){
        for(int i=0;i<16;i++) dp[j][i]=-inf;
    }
    dp[4][mask]=0;
    for(int i=4;i<n;i++){
        for(int j=0;j<16;j++){
            if(dp[i][j]==-inf) continue;
            for(int k=0;k<2;k++){
                int add=0,cm=j+k*(1<<4);
                for(pii x:s[i+1]) add+=((cm&x.fi) || ((cm^((1<<5)-1))&x.se));
                dp[i+1][cm>>1]=max(dp[i+1][cm>>1],dp[i][j]+add);
            }
        }
    }
    int res=0;
    for(int i=0;i<16;i++){
        int cur=dp[n][i],cm=i;
        if(cur==-inf) continue;
        for(int j=1;j<=4;j++){
            cm+=((mask>>(j-1))&1)*(1<<4);
            for(pii x:s[j]) cur+=((cm&x.fi) || ((cm^((1<<5)-1))&x.se));
            cm>>=1;
        }
        res=max(res,cur);
    }
    return res;
}
void solve(){
    cin >> n >> c;
    for(int i=1;i<=c;i++){
        int e,f,l,a,s1=0,s2=0;cin >> e >> f >> l;
        while(f--){
            cin >> a;a=(a-e+n)%n;
            if(a<=4) s1^=(1<<a);
        }
        while(l--){
            cin >> a;a=(a-e+n)%n;
            if(a<=4) s2^=(1<<a);
        }
        s[(e+3)%n+1].push_back({s1,s2});
    }
    int ans=0;
    for(int i=0;i<16;i++) ans=max(ans,cal(i));
    cout << ans << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}

