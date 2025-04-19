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
const int maxn=1000005;
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
int dp[maxn][4][4],f[2][4][4];
int g(int x,int t){
    if(t==0) return x;
    else if(t==1) return 0;
    else if(t==2) return 1;
    else return x^1;
}
void solve(){
    int n;cin >> n;
    vector<int> a(n+1),b(n+1);
    for(int i=1;i<=n;i++){char c;cin >> c;a[i]=c-'0';}
    for(int i=1;i<=n;i++){char c;cin >> c;b[i]=c-'0';}
    for(int i=0;i<=n;i++) for(int j=0;j<4;j++) for(int k=0;k<4;k++) dp[i][j][k]=inf;
    for(int i=0;i<2;i++) for(int j=0;j<4;j++) for(int k=0;k<4;k++) f[i][j][k]=g(g(i,j),k);
    dp[0][0][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<4;j++){
            for(int k=0;k<4;k++){
                int w=dp[i-1][j][k];
                if(((j==k) == (k>=1)) || w==inf) continue;
                dp[i][j][k]=min(dp[i][j][k],w);
                dp[i][0][j]=min(dp[i][0][j],w);
                dp[i][0][k]=min(dp[i][0][k],w);
                dp[i][0][0]=min(dp[i][0][0],w);
            }
        }
        for(int j=0;j<4;j++){
            for(int k=0;k<4;k++){
                if((j==k) == (k>=1)) continue;
                dp[i][j][k]=min(dp[i][j][k],dp[i][0][j]+1);
                dp[i][j][k]=min(dp[i][j][k],dp[i][0][k]+1);
                dp[i][j][k]=min(dp[i][j][k],dp[i][0][0]+2);
            }
        }
        for(int j=0;j<4;j++){
            for(int k=0;k<4;k++) if(f[a[i]][j][k]!=b[i]) dp[i][j][k]=inf;
        }
    }
    int ans=inf;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++) ans=min(ans,dp[n][i][j]);
    }
    cout << ans << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
