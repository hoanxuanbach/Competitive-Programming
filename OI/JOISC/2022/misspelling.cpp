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
const int mod=1e9+7;
const int maxn=200005;
const int bl=650;
const int maxs=650;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
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
void solve(){
    int n,m;cin >> n >> m;
    vector<vector<pii>> v(n+1);
    for(int i=1;i<=m;i++){
        int a,b,c=0;cin >> a >> b;
        if(a>b) swap(a,b),c=1;
        v[a].push_back({i,c});
        v[b].push_back({-i,c});
    }
    vector<int> del(m+1,0);
    vector<vector<int>> dp(n+1,vector<int>(26,0));
    vector<vector<pii>> lst(2);
    for(int i=1;i<=n;i++){
        for(int j=0;j<2;j++){
            while(!lst[j].empty() && del[lst[j].back().se]) lst[j].pop_back();
        }
        int p0=(lst[0].empty()?0:lst[0].back().fi);
        int p1=(lst[1].empty()?0:lst[1].back().fi);
        if(i==1){
            for(int j=0;j<26;j++) dp[i][j]=1;
        }
        else{
            int d=max(p0,p1);
            for(int j=0;j<26;j++){
                dp[i][j]=(dp[i-1][25]-dp[d][25]-dp[i-1][j]+dp[d][j]+(j>=1?dp[i-1][j-1]-dp[d][j-1]:0)+3*mod)%mod;
                if(p1<p0) dp[i][j]=(dp[i][j]+(j>=1?dp[d][j-1]-dp[p1][j-1]:0)+mod)%mod;
                else dp[i][j]=(dp[i][j]+dp[d][25]-dp[d][j]-dp[p0][25]+dp[p0][j]+2*mod)%mod;
            }
        }
        for(int j=1;j<26;j++) dp[i][j]=(dp[i][j]+dp[i][j-1])%mod;
        for(int j=0;j<26;j++) dp[i][j]=(dp[i][j]+dp[i-1][j])%mod;
        for(auto [p,c]:v[i]){
            if(p<0) del[-p]=1;
            else lst[c].push_back({i,p});
        }
    }
    cout << dp[n][25] << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
