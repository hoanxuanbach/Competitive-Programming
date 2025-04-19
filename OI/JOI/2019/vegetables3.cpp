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
int dp[202][202][202][3],cost[404][404];
void solve(){
    int n;string s;cin >> n >> s;
    vector<vector<int>> v(3);
    for(int i=0;i<3;i++) v[i].push_back(0);
    for(int i=0;i<n;i++) v[(s[i]=='R'?0:(s[i]=='G'?1:2))].push_back(i+1);
    int a=(int)v[0].size()-1,b=(int)v[1].size()-1,c=(int)v[2].size()-1;
    if(a+b+c+1<2*max({a,b,c})){
        cout << -1 << '\n';
        return;
    }
    for(int i=0;i<=a;i++) for(int j=0;j<=b;j++) for(int k=0;k<=c;k++) for(int d=0;d<=2;d++) dp[i][j][k][d]=inf;
    for(int i=1;i<=n;i++){
        for(int k=0;k<3;k++){
            int cur=0;
            for(int a:v[k]) cur+=(a>i),cost[i][a]=cur;
        }
    }
    for(int i=0;i<3;i++) dp[0][0][0][i]=0;
    for(int i=0;i<=a;i++) for(int j=0;j<=b;j++) for(int k=0;k<=c;k++){
        if(i>=1) dp[i][j][k][0]=min(dp[i-1][j][k][1],dp[i-1][j][k][2])+cost[v[0][i]][v[1][j]]+cost[v[0][i]][v[2][k]];
        if(j>=1) dp[i][j][k][1]=min(dp[i][j-1][k][0],dp[i][j-1][k][2])+cost[v[1][j]][v[0][i]]+cost[v[1][j]][v[2][k]];
        if(k>=1) dp[i][j][k][2]=min(dp[i][j][k-1][0],dp[i][j][k-1][1])+cost[v[2][k]][v[0][i]]+cost[v[2][k]][v[1][j]];
    }
    int ans=inf;
    for(int i=0;i<3;i++) ans=min(ans,dp[a][b][c][i]);
    cout << ans << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
